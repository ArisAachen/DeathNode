use std::net::{TcpListener, TcpStream};
use std::io::{Read, Write};
use std::fs;

fn main() {
    let listener = TcpListener::bind("127.0.0.1:7878").unwrap();
    for streamer in listener.incoming() {
        println!("connection established");
        let stream = streamer.unwrap();
        handle_connection(stream);
    }

    println!("Hello, world!");
}


fn handle_connection(mut stream: TcpStream) {
    let mut buf = [0; 1024];
    stream.read(&mut buf).unwrap();
    println!("request {}", String::from_utf8_lossy(&buf[..]));
    let contents = fs::read_to_string("hello.html").unwrap();
    let respon = format!("HTTP/1.1 200 OK\r\nContent-Length: {}\r\n {}", contents.len(), contents);
    println!("response is {}", respon);
    stream.write(respon.as_bytes()).unwrap();
    stream.flush().unwrap();
}

