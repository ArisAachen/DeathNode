use std::io;
use rand::Rng;
use std::cmp::Ordering;

fn read_num() {
    // read message
    println!("please input message");
    let mut input_message = String::from("prefor message ");
    let result = io::stdin().read_line(&mut input_message);
    result.expect("failed to read line");
    println!("all message is {}", input_message);
}

fn guess_game() {
    // gen rand number
    let guess_number = rand::thread_rng().gen_range(1..=100);
    println!("guess number is {}", guess_number);
    // read message
    loop {
        println!("input a number");
        let mut number = String::new();
        io::stdin().read_line(&mut number).expect("read input message failed");
        // transform number
        let number : i32 = match number.trim().parse() {
            Ok(num) => num,
            Err(_) => continue,
        };
        // compare number
        match number.cmp(&guess_number) {
            Ordering::Equal => {
                println!("number is correct");
                break;
            },
            _ => println!("input number is differ")
        }
    }
}

fn const_word() {
    const CONST_NUMBER : u32 = 1;
    println!("const number is {}", CONST_NUMBER);
}

fn tuple_test() {
    let tuple = (1, "message", 1.5);
    let (x, _, z) = tuple;
    println!("number is {0}, float is {1}", x, z);
}

fn ref_test() {
    let mut message = String::from("message");
    // mut 类型参数必须快速使用完成, 顺序调换则失败
    // 一个引用的作用域 是 从声明 到 最后使用
    ref_mut_string(&mut message); 
    let copy_message = &message;
    println!("copy message is {}", copy_message);
}

fn find_word() -> usize {
    let exp = String::from("abcde");
    let slice = &exp[0..3];
    println!("slice is {}", slice);

    for (index, &elem) in exp.as_bytes().iter().enumerate() {
        if elem == b' ' {
            return index;
        }
    }

    exp.len()
}

fn find_slice(slice : &str) -> &str {
    &slice[..slice.len() - 1]
}

fn ref_mut_string(message : &mut String) {
    message.push_str("append");
}

fn control_flower() {
    // 控制流必须返回同样的类型
    // let result = if true {5} else {"message"};
    let arr = [1, 2, 3, 4];
    for elem in (1..4).rev() {
        println!("elem contains {}", elem);
    }
}


#[derive(Debug)]
struct User {
    username: String,
    password: String,
    count: u16
}

struct Tuple (u16, u16, String);

fn user_constructor() {
    let username = String::from("arch");

    let user = User {
        username,
        password: String::from("password"),
        count: 1
    };

    println!("{:?}", user);

    dbg!(&user);
}

#[derive(Debug)]
struct Rectange {
    width : u32,
    height : u32
}

impl Rectange {
    fn new(width : u32, height: u32) -> Rectange {
        Rectange {
            width,
            height
        }
    }

    fn area(&self) -> u32{
        self.width * self.height
    }
}

fn calculate(rec : &Rectange) -> u32 {
    rec.width * rec.height
}

fn call_cal() {
    let body = Rectange {
        width : 1,
        height : 2
    };
    println!("box is {:?}, result: {}", body, calculate(&body));

    let body_r = Rectange::new(1, 2);
    println!("box is {:?}, result: {}", body_r, body_r.area());
}

#[derive(Debug)]
enum IpAddr {
    V4 (String),
    V6 (String)
}

fn out_addr() {
    let home = IpAddr::V4(String::from("127.0.0.1"));
    println!("addr is {:?}", home);
}

enum Message {
    None, 
    Num (u32),
    Info (String, u32)
}

fn if_let() {
    let let_num = Some(5);
    if let Some(num) = let_num {
        println!("num is {}", num);
    }
}

fn main() {
    println!("run game");
    // read_num();
    // guess_game();
    // const_word();
    // tuple_test();
    // ref_test();
    // find_word();
    // user_constructor();
    call_cal();
    out_addr();
}