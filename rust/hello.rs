use std::io;

fn read_num() {
    // read message
    println!("please input message");
    let mut input_message = String::new();
    let result : Result<usize> = io::stdin().read_line(&input_message);
    result.expect("failed to read line");
}


fn main() {
    println!("run game");
    read_num();
    println!("hello world!");
}