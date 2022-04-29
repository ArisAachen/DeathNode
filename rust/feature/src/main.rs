fn static_call(arg : &'static str) {
    println!("result is {}", arg);
}

fn static_test() {
    let msg = "ok";
    static_call(&msg);
}

use std::fmt::Display;
fn static_int<T: Display + 'static>(arg : T) {
    println!("static int is {}", arg);
}

fn vec_call(cnt: Vec<String>) -> Vec<String> {
    let mut tmp_cnt = cnt;
    tmp_cnt
}

fn func_return_call() -> u32 {
    12
}

fn func_use_return(num: &mut u32) {
    let num = *num + 12;
    println!("num is {}", num)
}

fn return_call_test() {
    func_use_return(&mut func_return_call());
}

use std::f32;
fn flocat_test() {
    let pi = 3.14f32;
    let radius = 5.00f32;

    let area = pi * f32::powi(radius, 2);

    println!(
        "The area of a circle with radius {:.2} is {:.5}!",
        radius, area
    )
}

fn vec_test() {
    let blank = String::from("!");
    let mut new_blank = blank;
    let cnt = vec![String::from("message"), String::from("ok"), new_blank];
    let new_cnt = vec_call(cnt);
}

fn main() {
    static_test();
    println!("Hello, world!");
    let num = 2;
    static_int(num);
    vec_test();
    return_call_test();
    flocat_test();
}
