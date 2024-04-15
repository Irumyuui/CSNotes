# Pipeline

```csharp
using System;
using System.Buffers;
using System.IO.Pipelines;
using System.Net;
using System.Threading.Tasks;
using System.Net.Sockets;
using System.Text;
using System.IO;
using Serilog;

Log.Logger = new LoggerConfiguration()
    .MinimumLevel.Information()
    .WriteTo.Console()
    .CreateLogger();

const string serverIp = "[::1]";
const int port = 11451;

using var server = new TcpServer(serverIp, port);
await server.StartAsync();


public sealed class TcpServer : IDisposable  {
    private readonly TcpListener _listener;

    private bool _disposed = false;

    public TcpServer(string serverIp, int port) => _listener = new TcpListener(IPAddress.Parse(serverIp), port);
    
    public async Task StartAsync() {
        _listener.Start();

        while (true) {
            var client = await _listener.AcceptTcpClientAsync();
            Log.Information($"Client connected: {client.Client.RemoteEndPoint}");
            _ = HandleClientAsync(client);
        }
    }
    
    ~TcpServer() => Dispose(false);
    
    public void Dispose() {
        Dispose(true);
        GC.SuppressFinalize(this);
    }

    private void Dispose(bool disposing) {
        if (_disposed)
            return;
        
        if (disposing) {
            _listener.Dispose();
        }
        _disposed = true;
    }

    private static async Task HandleClientAsync(TcpClient client) {
        try {
            var pipe = new Pipe();
            var writing = FillPipeAsync(client.GetStream(), pipe.Writer);
            var reading = ReadPipeAsync(pipe.Reader);
            await Task.WhenAll(reading, writing);
        } finally {
            Log.Information("Client disconnected");
            client.Dispose();   
        }
    }

    private static async Task FillPipeAsync(Stream stream, PipeWriter writer) {
        const int minimumBufferSize = 512;

        while (true) {
            var memory = writer.GetMemory(minimumBufferSize);
            try {
                var bytesRead = await stream.ReadAsync(memory);
                if (bytesRead == 0) {
                    break;
                }

                writer.Advance(bytesRead);
            } catch (Exception) {
                break;
            }

            var result = await writer.FlushAsync();

            if (result.IsCompleted) {
                break;
            }
        }

        await writer.CompleteAsync();
    }

    private static async Task ReadPipeAsync(PipeReader reader) {
        while (true) {
            var result = await reader.ReadAsync();
            var buffer = result.Buffer;

            // 这边找结束符号
            SequencePosition? position = buffer.PositionOf((byte)'\n');

            if (position is null) {
                continue;
            }
            
            var line = buffer.Slice(0, position.Value);
            var message = Encoding.UTF8.GetString(line);
            Console.WriteLine(message);
            
            buffer = buffer.Slice(buffer.GetPosition(1, position.Value));
            reader.AdvanceTo(buffer.Start, buffer.End);

            if (result.IsCompleted) {
                break;
            }
        }

        await reader.CompleteAsync();
    }
}
```
