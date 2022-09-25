#include <algorithm>
#include <cctype>
#include <functional>
#include <iterator>
#include <regex>
#include <stack>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
using namespace std;

void snake_matrix() {
    std::cout << "snake_matrix" << std::endl;
    int number = 4;
    // std::cin >> number;

    std::vector<std::vector<int>> results;
    std::vector<int> first_line(number, 1);
    for (int index = 1; index < first_line.size(); index++)
        first_line[index] = first_line[index - 1] + (index + 1);
    results.push_back(std::move(first_line));
    for (int index = 1; index < number; index++) {
        std::vector<int> tmp;
        std::transform(results[index - 1].begin() + 1, results[index - 1].end(),
        std::back_inserter(tmp), [](int value) {
            return value - 1;
        });
        results.push_back(std::move(tmp));
    }
    for (const auto& result : results) {
        for (auto elem : result) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }    
}

void split() {
    std::string input = "I123am*a*student";
    std::regex reg("[^a-zA-Z\\s]");
    input = std::regex_replace(input, reg, " ");
    reg = " ";
    std::cout << "originx: " << input << std::endl;
    std::sregex_token_iterator iter(input.begin(), input.end(), reg, -1);
    std::sregex_token_iterator end;
    std::vector<std::string> results;
    std::copy_if(iter, end, std::back_inserter(results), [](std::string elem) {
        return elem.find(" ") == std::string::npos && elem != "";
    });
    for (auto pos = results.rbegin(); pos != results.rend(); pos++)
        std::cout << *pos << " ";    
}



class OpPriority {
public:
    bool operator()(char first, char second) {
        static std::unordered_map<char, int> comp_ {
            {'*', 1}, 
            {'/', 1},
            {'+', 2},
            {'-', 2},
        };
        // std::cout << "compare: " << first << ", " << second << std::endl;
        return comp_.at(first) < comp_.at(second);
    }
};


// void stack_cal() {
//     std::stack<int> num_stack;
//     std::stack<char> op_stack;

//     // input 
//     std::string input("-1*(-1-1)");
//     std::regex reg(R"(\W)");
//     std::sregex_token_iterator iter(input.begin(), input.end(), reg, {-1, 0});
//     std::sregex_token_iterator end;

//     for (; iter != end; iter++) {
//         std::cout << "iter: "<< *iter << std::endl;
//         if (*iter == "" || *iter == " ")
//             continue;
//         else if (iter->str().find_first_not_of("0123456789") == std::string::npos) 
//             num_stack.push(std::stoi(*iter));
//         else if (iter->str()[0] == ')') {
//             while (op_stack.top() != '(') {
//                 char op = op_stack.top();
//                 op_stack.pop();
//                 int result = op_on_stack(num_stack, op);
//             }
//             op_stack.pop();
//         }   
//         else {
//             if (op_stack.empty()) 
//                 op_stack.push(iter->str()[0]);
//             else if (OpPriority{}(iter->str()[0], op_stack.top()))
//                 op_stack.push(iter->str()[0]);
//             else {
//                 while (!op_stack.empty() && !OpPriority{}(iter->str()[0], op_stack.top())) {
//                     char op = op_stack.top();
//                     op_stack.pop();
//                     int result = op_on_stack(num_stack, op);
//                 }
//                 op_stack.push(iter->str()[0]);
//             } 
//         }
//     }
    
//     while (!op_stack.empty()) {
//         char op = op_stack.top();
//         op_stack.pop();
//         int result = op_on_stack(num_stack, op);
//     }

//     // std::cout << "stack size: " << num_stack.size() << ", result: " << num_stack.top() << std::endl;
// }


/**
 * @brief 
 * import java.io.IOException;
import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.util.Stack;
public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String line = br.readLine();
        System.out.println(calculate(line));
    }
    public static int calculate(String line){
        Stack<Integer> stack = new Stack<>();
        char sign = '+';
        int number = 0;
        int len = line.length();
        char[] chars = line.toCharArray();
        for(int i = 0; i < len; i++){
            char ch = chars[i];
            if(ch == ' ')continue;
            if(Character.isDigit(ch)){
                number = number * 10 + ch - '0';
            }
            if(ch == '('){
                int count = 1;
                int j = i + 1;
                while(count > 0){
                    if(chars[j] == ')')count--;
                    if(chars[j] == '(')count++;
                    j++;
                }
                //递归，解小括号中的表达式
                number = calculate(line.substring(i + 1, j - 1));
                i = j - 1;
            }
            if(!Character.isDigit(ch) || i == len - 1){
                if(sign == '+'){
                    stack.push(number);
                }else if(sign == '-'){
                    stack.push(-1 *number);
                }else if(sign =='*'){
                    stack.push(stack.pop() * number);
                }else if(sign == '/'){
                    stack.push(stack.pop() / number);
                }
                //更新符号
                sign = ch;
                //刷新数字
                number = 0;
            }
        }
        //栈中数字求和得到结果
        int ans = 0;
        while (!stack.isEmpty()) {
            ans += stack.pop();
        }
        return ans;
    }
}

 */


bool op_priority(char first, char second) {
    static std::unordered_map<char, int> comp_ {
        {'*', 1}, 
        {'/', 1},
        {'+', 2},
        {'-', 2},
    };
    return comp_.at(first) < comp_.at(second);
}

int op_on_stack(std::stack<int>& num_stack, char op) {
    if (num_stack.empty())
        return -1;
    int first_num, second_num;
    second_num = num_stack.top();
    num_stack.pop();
    if (num_stack.size() == 0) {
        first_num = 0;
    } else {
        first_num = num_stack.top();
        num_stack.pop();        
    }
    int result;
    switch (op) {
    case '*':
        result = first_num * second_num;
        break;
    case '/':
        result = first_num / second_num;
        break;
    case '+':
        result = first_num + second_num;
        break;
    case '-':
        result = first_num - second_num;
        break;
    }
    std::cout << first_num << op << second_num 
        << "=" << result << std::endl;
    num_stack.push(result);
    return result;
}

int calculate_input(const std::string& input) {
    std::stack<int> num_stack;
    std::stack<char> op_stack;

    int num = 0;
    for (int index = 0; index < input.length(); index++) {
        char ch = input[index];
        if (ch == ' ') 
            continue;
        if (std::isdigit(ch)) {
            num = num * 10 + ch - '0';
            if (index == input.length() - 1)
                num_stack.push(num);
        }
        else if (ch == '(') {
            int match = 1;
            int pos = index;
            while (ch != ')' || match > 0) {
                pos++;
                ch = input[pos];
                if (ch == ')') match--;
                if (ch == '(') match++;
            }
            auto sub = input.substr(index + 1, pos - index -1);
            std::cout << "sub: " << sub << ", pos: " << pos << std::endl;
            num = calculate_input(sub);
            index = pos;
            if (index == input.length() - 1)
                num_stack.push(num);
        } else {
            num_stack.push(num);
            num = 0;
            if (op_stack.empty())
                op_stack.push(ch);
            else if (op_priority(ch, op_stack.top()))
                op_stack.push(ch);
            else {
                while (!op_stack.empty() && !op_priority(ch, op_stack.top())) {
                    char op = op_stack.top();
                    op_stack.pop();
                    op_on_stack(num_stack, op);
                }
                op_stack.push(ch);
            }
        }
    }

    while (!op_stack.empty()) {
        char op = op_stack.top();
        op_stack.pop();
        op_on_stack(num_stack, op);
    }

    return num_stack.top();
}

int main() {
    // 208 -9 + 3 + 9 - 6
    std::cout << "result: " << calculate_input("(7+4*3+10*(3-3+4-1-8-10))") << std::endl;
    return 0;
}

