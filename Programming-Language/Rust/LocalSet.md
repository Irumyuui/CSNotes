```rust
use std::time::Duration;

use tokio::task::LocalSet;

fn main() -> anyhow::Result<()> {
    tracing_subscriber::fmt().init();

    let rt = tokio::runtime::Builder::new_current_thread()
        .enable_all()
        .build()?;

    rt.block_on(LocalSet::new().run_until(async move {
        let (rx, tx) = async_channel::unbounded::<u32>();
        let (r, t) = async_channel::unbounded::<u32>();

        tokio::task::spawn_local(async move {
            let mut tick = tokio::time::interval(Duration::from_secs(2));
            loop {
                tokio::select! {
                    _ = tick.tick() => {
                        tracing::info!("tick!");
                    }
                    x = tx.recv() => {
                        let Ok(x) = x else {
                            tracing::info!("recv: closed");
                            return;
                        };
                        tracing::info!("recv: {:?}", x);
                        r.send(x).await.unwrap();
                    }
                }
            }
        });

        for x in 0..10 {
            let res = rx.send(x).await;
            tracing::info!("send: {:?}", res);
            let res = t.recv().await;
            tracing::info!("recv2: {:?}", res);
        }
    }));

    Ok(())
}
```