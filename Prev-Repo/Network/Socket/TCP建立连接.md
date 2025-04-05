# TCP 建立连接

使用套接字建立 `TCP` 连接。

## TCPServer

服务端连接过程：

1. `socket`: 创建套接字
2. `bind`: 绑定 IP 地址和端口
3. `listen`: 监听连接
4. `accept`: 等待客户端连接
5. 接收/发送数据

```csharp
using System.Net;
using System.Net.Sockets;
using System.Text;

const string ServerIP = "127.0.0.1";
const int ServerProt = 11451;

// Create socket.
using var socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

// Bind socket to IP and port.
var endPoint = new IPEndPoint(IPAddress.Parse(ServerIP), ServerProt);
socket.Bind(endPoint);

// Listen for incoming connections.
socket.Listen();

// Accept incoming connections.
// Send "Hello, client!" message to client.
while (true) {
    using var connections = await socket.AcceptAsync();
    await connections.SendAsync(Encoding.UTF8.GetBytes("Hello, client!"));
    Console.WriteLine("Sent message to client.");
}
```

## TCPClient

客户端连接到服务端过程：

1. `socket`: 创建套接字
2. `connect`: 连接到服务器
3. 接收/发送数据

```csharp
using System.Net;
using System.Net.Sockets;
using System.Text;

const string ServerIP = "127.0.0.1";
const int ServerProt = 11451;

// Create a TCP/IP socket.
using var socket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);

// Connect the socket to the server.
var endPoint = new IPEndPoint(IPAddress.Parse(ServerIP), ServerProt);
await socket.ConnectAsync(endPoint);

// Read data from the server.
var buffer = new byte[1024];
var byteLength = await socket.ReceiveAsync(buffer);

Console.WriteLine($"Received: {Encoding.UTF8.GetString(buffer, 0, byteLength)}");
```
