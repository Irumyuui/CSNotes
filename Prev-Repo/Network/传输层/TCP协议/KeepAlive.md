# KeepAlive

`KeepAlive` 机制是由操作系统为了节省连接资源而提供的，在 TCP 协议中不包含此机制。

具体来说，就是如果对方的连接突然中断，那么这边的连接还在持续着，但此次连接已经失效，因此需要发送一些探测报文，看对方是否仍然在连接，否则就释放连接资源。

test test

```csharp
public static class SocketExtensions
{
    /// <summary>
    /// 开启 TCP KeepAlive 机制
    /// 设置 KeepAlive 参数
    /// </summary>
    /// <param name="self"></param>
    /// <param name="tcpKeepAliveTime">KeepAlive 心跳时间</param>
    /// <param name="tcpKeepAliveInterval">没有收到确认，继续发送 KeepAlive 包的间隔时间</param>
    /// <param name="tcpKeepAliveRetryCount">KeepAlive 重试次数</param>
    static void SetKeepAlive(this Socket self, int tcpKeepAliveTime, int tcpKeepAliveInterval, int tcpKeepAliveRetryCount)
    {
        self.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.KeepAlive, true);
        self.SetSocketOption(SocketOptionLevel.Tcp, SocketOptionName.TcpKeepAliveInterval, tcpKeepAliveInterval);
        self.SetSocketOption(SocketOptionLevel.Tcp, SocketOptionName.TcpKeepAliveTime, tcpKeepAliveTime);
        self.SetSocketOption(SocketOptionLevel.Tcp, SocketOptionName.TcpKeepAliveRetryCount, tcpKeepAliveRetryCount);
    }
}
```
