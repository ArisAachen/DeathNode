use std::env;




fn main() {
    let args : Vec<String> = env::args().collect();

    minigrep::parse_config(&args);

}






