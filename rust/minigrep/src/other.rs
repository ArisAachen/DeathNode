fn larger_str<'a>(first: &'a str, second : &'a str) -> &'a str {
    if first.len() > second.len() {
        return first
    }
    second
}

fn get_larger_message() {
    let first = String::from("frist"); 
    let mut larger = String::new();
    {
        let second = String::from("second");
        println!("larger one is {}", larger);
    }
    
}

// read message from file
fn read_file(filename : &str) -> Result<String, io::Error> {
    // open file
    let mut file_obj = fs::File::open(filename)?;
    // read message from stream
    let mut info = String::new();
    file_obj.read_to_string(&mut info)?;
    println!("message is {}", info);
    Ok(info)
}