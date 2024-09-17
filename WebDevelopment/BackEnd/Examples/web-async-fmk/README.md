# 异步后端框架

一个异步网络后端框架。

主要结构为：

- `async main` ：也就是主入口
- `xxx Server` ：管理所有连接的服务器
- `xxx Handler` ：处理每个连接的请求

`Server` 侦听所有连接到该地址的连接，并为每个连接创建 `Handler` 处理请求。

`Handler` 负责处理每个连接的请求，并将结果返回给客户端。

```rust
#[derive(Debug)]
struct TcpServer {
    // tpc 连接监听器
    listener: TcpListener,
    // 限制最大连接数
    limit_connections: Arc<Semaphore>,

    // 关闭信号
    notify_shutdown: broadcast::Sender<()>,

    shutdown_complete_tx: mpsc::Sender<()>,
    
    // services
    // 一般这里是放一些服务的，看情况是不是单例或者什么的
    // 如果或不要的话，也可以在 run 中自己手动指定
}

impl TcpServer {
    /// 处理连接
    async fn run(&mut self) -> crate::Result<()> {
        println!("TcpServer running");

        loop {
            let permit = self
                .limit_connections
                .clone()
                .acquire_owned()
                .await
                .unwrap();
            // let (socket, _) = self.listener.accept().await?;
            let socket = self.accept().await?;

            let mut handler = Handler {
                connection: Conn::new(socket),
                shutdown: Shutdown::new(self.notify_shutdown.subscribe()),
                _shutdown_complete: self.shutdown_complete_tx.clone(),
            };

            tokio::spawn(async move {
                if let Err(e) = handler.run().await {
                    println!("Error: {}", e);
                }
                drop(permit);
            });
        }
    }

    /// 连接重试
    async fn accept(&mut self) -> crate::Result<TcpStream> {
        let mut try_count = 0;
        loop {
            match self.listener.accept().await {
                Ok((socket, _)) => return Ok(socket),
                Err(err) => {
                    if try_count >= 4 {
                        return Err(err.into());
                    }
                }
            }

            tokio::time::sleep(std::time::Duration::from_secs(1 << try_count)).await;
            try_count += 1;
        }
    }
}

struct Handler {
    // service: Box<dyn Service + Send + Sync>,
    connection: Conn,
    shutdown: Shutdown,
    _shutdown_complete: mpsc::Sender<()>,

    // 放点服务
}

impl Handler {
    async fn run(&mut self) -> crate::Result<()> {
        while !self.shutdown.is_shutdown() {
            // 主要通过 Conn 来处理逻辑
            let _ = tokio::select! {
                _ = self.shutdown.recv() => {
                    return Ok(());
                }
            };
            // 读取数据
            // 解析指令
            // 调用服务
            // 发送数据
        }

        Ok(())
    }
}

// 根据服务自定
#[derive(Debug)]
pub(crate) struct Conn {
    stream: BufWriter<TcpStream>,
    buffer: BytesMut,
}

impl Conn {
    pub fn new(socket: TcpStream) -> Self {
        Self {
            stream: BufWriter::new(socket),
            buffer: BytesMut::with_capacity(8192),
        }
    }

    pub async fn read_frame(&mut self) -> crate::Result<Option<()>> {
        todo!()
    }

    // pub async fn write_frame(&)
}

// 实现优雅关闭
pub(crate) struct Shutdown {
    is_shutdown: bool,
    notify_shutdown: broadcast::Receiver<()>,
}

impl Shutdown {
    pub(crate) fn new(notify_shutdown: broadcast::Receiver<()>) -> Self {
        Self {
            is_shutdown: false,
            notify_shutdown,
        }
    }

    pub(crate) fn is_shutdown(&self) -> bool {
        self.is_shutdown
    }

    pub(crate) async fn recv(&mut self) {
        if self.is_shutdown {
            return;
        }

        let _ = self.notify_shutdown.recv().await;
        self.is_shutdown = true;
    }
}
}

```