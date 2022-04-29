use std::thread;
use std::sync::{mpsc, Arc, Mutex};

pub struct ThreadPool {
    workers: Vec<Worker>,
    sender: mpsc::Sender<Job>,
};

impl ThreadPool {
    pub fn new(size: usize) -> ThreadPool {
        // create channel
        let (sender, receiver) = mpsc::channel();
        let mut workers = Vec::with_capacity(size);
        for id in 0..size {
            workers.push(Worker::new(id));
        }
        ThreadPool { workers,sender }
    }

    pub fn execute<F>(&self, f:F) 
    where 
        F: FnOnce() + Send + 'static {
        let Job = Box::new(f);
        self.sender.send(job).unwrap();
    }
}

struct Worker {
    id: usize,

    thread: thread::JoinHandle<()>,
}

impl Worker {
    fn new(id: usize, receiver: Arc<Mutex<mpsc::Receiver<Job>>>) -> Worker {
        // worker elements
        let thread = thread::spawn(move || loop {
            let job = receiver.lock().unwrap();

        });
        Worker {id, thread}
    }
}

type Job = Box<dyn FnOnce() + Sender + 'static>;