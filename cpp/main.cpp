

#include <iostream>
#include <cstring>

void test_get_line() {
    const int size = 20;
    char msg[size];
    memset(&msg, 0, sizeof(msg));

    while (strcmp(msg, "end") != 0)
    {
        std::cout << R"(please input message, use "end" to finish)" << std::endl;
        std::cin.getline(msg, size);
        std::cout << "input message is " << msg << std::endl;
    }

    std::cout << "get line end" << std::endl;

}


void test_struct() {
    struct test {
        std::string msg;
    } one, two;


    struct {
        std::string msg;
    } three;


}

void test_ano_union () {
    struct test {
        union 
        {
            std::string message;
            int id;
        };
        
    } only ;

    only.message = "test";



}



int main() {

    test_get_line();



    return 1;
}