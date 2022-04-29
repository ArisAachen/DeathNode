use std::io::{self, Read};
use std::process;
use std::error;

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn read_line() {
        let info = String::from("message ok,
        found message");
        let query = String::from("query");
        assert_eq!(vec!["found message"], search(&query, &info));

    }

}


fn search<'a>(query : &str, contents: &'a str) -> Vec<&'a str> {
    let mut result = Vec::new();
    // read line 
    for line in contents.lines() {
        if line.contains(query) {
            result.push(line);
        }
    }
    result
}

/// config 
pub struct Config {
    pub filename : String,
    pub query_info : String
}

impl Config {
    fn new(args : &[String]) -> Result<Config, &'static str> {
        if args.len() < 3 {
            return Err("not ethough arguments");
        }
        let cfg = Config{ filename: args[1].clone(), query_info: args[2].clone()};
        Ok(cfg)
    }
}

pub fn read_file() {
    let pack = |mem| -> u32 {
        mem
    };
}

// parse config
pub fn parse_config(args : &[String]) -> Result<Config, Box<dyn error::Error>> {
    // check length 
    if args.len() < 3 {
        panic!("args length is not legal");
    }
    let result = Config::new(&args)?;
    Ok(result)
}

struct Cacher<T> 
where T : Fn(u32) -> u32 {
    calculate : T,
    value : Option<u32>
}

impl<T> Cacher <T> 
where T : Fn(u32) -> u32 {
    fn cal(&mut self, num: u32) ->u32 {
        match self.value {
            None => {
                self.value = Some(num);
                num
            },
            Some(val) => val
        }
    }
}


trait DecroMessage {
    fn out();
}

struct ConcretMessage(u32, String, u32);

impl DecroMessage for ConcretMessage {
    fn out() {
        println!("this is a decro message");
    }
}

trait DecroBlank {
    fn blank();
}

impl <T: DecroMessage> DecroBlank for T {
    fn blank() {
        println!("decro variant blank");
    }
}

fn blank_test() {
    let concret = ConcretMessage(1, String::from(""), 2);
    concret.blank();
}