# UDP 建立连接

## UDPServer

1. 创建一个 UDP Socket。
2. 绑定 Socket 到服务器的 IP 和端口。
3. 等待客户端向这个服务器的 IP 和端口发送数据并接收。

```csharp
using System.Net;
using System.Net.Sockets;
using System.Text;

const string ServerIP = "127.0.0.1";
const int ServerProt = 11451;

// Create a UDP socket.
using var socket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);

// Bind the socket to the server IP and port.
socket.Bind(new IPEndPoint(IPAddress.Parse(ServerIP), ServerProt));

// Wait for incoming data.
byte[] buffer = new byte[1024];
while (true) {
    EndPoint clientEndPoint = new IPEndPoint(IPAddress.Any, 0);
    var result = await socket.ReceiveFromAsync(buffer, clientEndPoint);
    
    var message = Encoding.UTF8.GetString(buffer[0..result.ReceivedBytes]);
    
    Console.WriteLine(
        $"[Server] IP: {(result.RemoteEndPoint as IPEndPoint)?.Address?.ToString() ?? ""}:{(result.RemoteEndPoint as IPEndPoint)?.Port.ToString() ?? "" } => {message}"
    );

    // await socket.SendToAsync(buffer[0..result.ReceivedBytes], result.RemoteEndPoint);
}
```

## UDPClient

1. 创建一个 UDP Socket。
2. （可选）绑定 Socket 到服务器的 IP 和端口。
3. 向指定 IP:Port 发送数据。
   如果之前已经绑定了 Socket，则可以直接使用 `socket.SendToAsync` 方法。

```csharp
using System.Net;
using System.Net.Sockets;
using System.Text;

const string ServerIP = "127.0.0.1";
const int ServerPort = 11451;

// Create a UDP socket.
using var socket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, ProtocolType.Udp);

// Send a message to the server.
await socket.ConnectAsync(new IPEndPoint(IPAddress.Parse(ServerIP), ServerPort));

while (true) {
    var message = Console.ReadLine();
    if (string.IsNullOrEmpty(message)) {
        continue;
    }
    if (message is "q") {
        break;
    }

    await socket.SendAsync(Encoding.UTF8.GetBytes(message));

    // IPEndPoint serverPoint = new IPEndPoint(IPAddress.Parse(ServerIP), ServerPort);
    // await socket.SendToAsync(
    //     Encoding.UTF8.GetBytes(message), serverPoint
    // );    
}
```
