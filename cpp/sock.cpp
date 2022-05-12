
#include <cerrno>
#include <cstring>
#include <iostream>

#include <string>
#include <thread>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void client() {
    auto lambda = []() {
        while (true) {
            int cl_fd = socket(AF_INET, SOCK_STREAM, 0);
            sockaddr_in server_addr;
            server_addr.sin_port = htons(12344);
            server_addr.sin_family = AF_INET;
            if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr.s_addr) == -1) {
                std::cout << "convert addr failed" << strerror(errno) << std::endl;
                return;
            }
            if (connect(cl_fd, (sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
                std::cout << "connect failed " << strerror(errno) << std::endl;
                return;
            }

            std::cout << "prepare send" << std::endl;
            std::string message = "client send";
            if (send(cl_fd, message.c_str(), message.length(), 0) < 0) {
                std::cout << "send failed" << strerror(errno) << std::endl;
                return;        
            }
            std::cout << "send end" << std::endl;
            // sleep(5);
            close(cl_fd);
        }
    };
    std::thread threads[30];
    for (int index = 0; index < 30; index++) {
        threads[index] = std::thread(lambda);
    }

    for (int index = 0; index < 30; index++) {
        threads[index].join();
    }
}


int main() {
    client();
    return 1;
}