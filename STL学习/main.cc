#include <list>
#include <stack>
#include <queue>
#include <string>
#include <utility>
#include <map>
#include <vector>

void use_stack() {
    std::stack<int, std::vector<int>> use;
    use.push(1);
    use.push(2);
    use.push(3);
    use.push(4);
    use.push(5);

    std::queue<int, std::vector<int>> tmp;
    tmp.push(1);
    tmp.push(2);
    tmp.push(3);
    tmp.push(4);
    tmp.push(5);

    std::pair<int, std::string> value(1, "");
    std::map<int, std::string> value_map;
    value_map.insert(value);
    value_map.insert(value);
    value_map.insert(value);
    value_map.insert(value);
}