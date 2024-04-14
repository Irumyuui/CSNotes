# Proator 模式

> proactor: 你给我收十个字节，收好了跟俺说一声。

其实就是完全的异步操作。发起 IO 请求以后，IO 操作在操作系统内核线程中进行，进行完通知一下用户进程。

```csharp
using System.Net;
using System.Net.Sockets;
using System.Text;

const string ServerIP   = "127.0.0.1";
const int    ServerPort = 11451;

using var server = new TcpListener(IPAddress.Parse(ServerIP), ServerPort);

server.Start();

Memory<byte> buffer = new byte[1 << 16];

while (true) {
    using var client = await server.AcceptTcpClientAsync();
    using var stream = client.GetStream();

    while (true) {
        var bytesRead = await stream.ReadAsync(buffer);
        if (bytesRead == 0) 
            break;
        
        var message = Encoding.UTF8.GetString(buffer.Span[..bytesRead]);
        Console.WriteLine($"Client => {message}");
    }
}
```
