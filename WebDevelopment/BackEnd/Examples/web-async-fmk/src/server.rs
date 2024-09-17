use std::{fmt::Debug, future::Future, sync::Arc};

use bytes::BytesMut;
use tokio::{
    io::BufWriter,
    net::{TcpListener, TcpStream},
    sync::{broadcast, mpsc, Semaphore},
};

// use crate::service::Service;

#[derive(Debug)]
struct TcpServer {
    // tpc 连接监听器
    listener: TcpListener,
    // 限制最大连接数
    limit_connections: Arc<Semaphore>,

    // 关闭信号
    notify_shutdown: broadcast::Sender<()>,

    shutdown_complete_tx: mpsc::Sender<()>,
    // service: dyn Service + Send + Sync,

    // services
}

impl TcpServer {
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

/// 根据服务自定
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

// #[derive(Debug)]
struct Handler {
    // service: Box<dyn Service + Send + Sync>,
    connection: Conn,
    shutdown: Shutdown,
    _shutdown_complete: mpsc::Sender<()>,
}

impl Handler {
    async fn run(&mut self) -> crate::Result<()> {
        while !self.shutdown.is_shutdown() {
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

pub async fn run(listener: TcpListener, shutdown: impl Future) {
    let (notify_shutdown, _) = broadcast::channel(1);
    let (shutdown_complete_tx, mut shutdown_complete_rx) = mpsc::channel(1);

    let mut server = TcpServer {
        listener,
        limit_connections: Arc::new(Semaphore::new(100)),
        notify_shutdown,
        shutdown_complete_tx,
    };

    tokio::select! {
        res = server.run() => {
            if let Err(e) = res {
                eprintln!("Error: {}", e);
            }
        }
        _ = shutdown => {
            println!("shutdown");
        }
    }

    drop(server.notify_shutdown);
    drop(server.shutdown_complete_tx);

    let _ = shutdown_complete_rx.recv().await;
}
