use std::io::{self, Read};
use std::fs::File;

fn use_string() {
    let head = String::from("head");
    let mut second = String::from("second");
    let combine = head + &second;
    second.push_str("add");
    println!("combine is {}", combine);
}

fn read_file(filename : &String) -> Result<String, io::Error> {
    let mut fObj = File::open(filename)?;
    let mut message = String::new();
    fObj.read_to_string(&mut message)?;
    return Ok(message);
}

struct Point<X1, Y1> {
    x: X1,
    y: Y1
}

impl<X1,Y1> Point<X1, Y1> {
}

trait Summary {
    fn Call(&self) -> String;
}

struct Tweeter {

}

impl Summary for Tweeter {
    fn Call(&self) -> String {
        String::from("tweeter")
    }
}

fn par_call<T, U>(t : &T, u: &U) 
    where T: Summary{

}

fn larger<T: std::cmp::PartialOrd + Copy> () {

}

struct Notifier<T: Summary> {
    notifier : T
}


trait Login {
    fn login();
}

impl<T: Summary> Login for T {
    fn login() {
        println!("account login");
    }
}


fn trait_notifier() {
    let notify = Notifier {
        notifier: Tweeter{

        }, 
    };

    let tweeter = Tweeter{};
    tweeter.Call();
    tweeter.login();
}



fn main() {
    use_string();
    println!("Hello, world!");
}
