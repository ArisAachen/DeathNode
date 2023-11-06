use std::io::{BufRead, BufReader};
use std::net::TcpStream;
use std::{result, io::Result, net::TcpListener};
use std::fmt;

pub struct Config {
    addr: String,
    port: u16,
}

// impl implement for Config
impl Config {
    // build Config
    fn parse_config(line: &str) -> Self {
        // split line with 
        let info_sl: Vec<&str> = line.split(':').collect();
        let port: u16 = info_sl[1].parse().expect("convert to port failed");
        Config { addr: info_sl[0].to_string(), port }
    }
}

impl fmt::Display for Config {
   fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
      write!(f, "{}", "nothing") 
   } 
}

pub fn tcp_start(cfg: &Config) -> Result<()> {
    let listener = TcpListener::bind(cfg.to_string())?;
    for incomer in listener.incoming() {
        match incomer {
            Err(err) => Err(err),
            Ok(stream) => handle_conn(&mut stream),
        }
    }
    Ok(())
}

// handle_conn handle tcp conn
fn handle_conn(stream: &mut TcpStream) {
    let reader = BufReader::new(stream);
    reader.
}
