#[cfg(test)]
mod tests {
    #[test]
    fn it_works() {
        let result = 2 + 2;
        assert_eq!(result, 4);
    }

    use super::front_of_house;
    
    #[test]
    fn white_list() {
        front_of_house::hosting::add_to_whitelist();
        assert!(1 == 1);
    }

    use super::use_for_test;
    #[test]
    fn module_test() {
        let first = use_for_test::Module::new();
        let second = use_for_test::Module::new();
        assert_ne!(first, second, "value must be not the same: {:?}, {:?}", first, second);
    }

    #[test]
    #[should_panic]
    fn index_test() {
        let first = use_for_test::Module::new();
        first.check();
    }
}


mod front_of_house;
fn call_module() {
    crate::front_of_house::hosting::add_to_whitelist()
}

mod use_for_test {
    #[derive(Debug)]
    pub struct Module {
        module_name : String,
        module_index : u32
    }

    impl Module {
        pub fn new() -> Module {
            return Module{
                module_name: "module".to_string(),
                module_index: 1,
            }
        }

        pub fn check(&self) {
            if self.module_index == 1 {
                panic!("index is illegal")
            }
        }
    }

    impl PartialEq for Module {
        fn eq(&self, other: &Self) -> bool {
            self.module_name == other.module_name && 
                self.module_index == other.module_index
        }
    }
}