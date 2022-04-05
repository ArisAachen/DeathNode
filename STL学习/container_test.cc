#include <cstdio>
#include <iostream>
#include <iterator>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>
#include <deque>
#include <algorithm>

void vector_test() {
    std::vector<int>::iterator it;
}

// 必须确保迭区间算法迭代器是同一个容器的
// 以下会抛出异常
void vector_range_test() {
    std::vector<int> first ({1,2,3});
    std::vector<int> second ({1,2,3});
    std::sort(first.begin(), second.end());
    
    std::cout << "end" << std::endl;
}

// 必须确保第二个区间大于等于第一个
// 否则段错误
void vector_size_test() {
    std::vector<int> first ({1,2,3});
    std::vector<int> second;
    std::copy(first.cbegin(), first.cend(), second.begin());
}

// 安插型迭代器会自动扩展长度
// 必须确保迭代器的操作对于容器是合法的
// 例如 vector 只允许 push_back, 使用 front_inserter 会编译报错 
void vector_inserter_test() {
    std::deque<int> first ({1,2,3});
    std::vector<int> second ({4,5,6});

    std::copy(second.cbegin(), second.cend(), std::front_inserter(first));
    for (const auto iter : first) {
        std::cout << iter << " ";
    }
    std::cout << std::endl;

    std::copy(first.cbegin(), first.cend(), std::inserter(second, second.begin()+3));
    for (const auto iter : second) {
        std::cout << iter << " ";
    }
    std::cout << std::endl;


    std::vector<std::string> input_sl;
    std::copy(std::istream_iterator<std::string>(std::cin), std::istream_iterator<std::string>(), std::back_inserter(input_sl));
    for (const auto iter : second) {
        std::cout << iter << " ";
    }
    std::cout << std::endl;
}

void vector_change_test() {
    std::vector<int> vec_int {1, 2, 3, 3, 4};
    auto pos = std::remove(vec_int.begin(), vec_int.end(), 3);
    std::cout << "remove value is " << *pos << std::endl;
    std::cout << "distance is " << std::distance(pos, vec_int.end()) << std::endl;

    vec_int.erase(pos, vec_int.end());
}

int square(int value) {
    return value * value;
}

void vector_alfunc_test() {
    std::vector<int> vec_int {1, 2, 3, 3, 4};
    std::transform(vec_int.begin(), vec_int.end(), vec_int.begin(), square);
    std::for_each(vec_int.cbegin(), vec_int.cend(), [](int a) { std::cout << a << " "; });
    std::cout << std::endl;

    std::sort(vec_int.begin(), vec_int.end(), [](int a, int b) { return a < b;});
    std::for_each(vec_int.cbegin(), vec_int.cend(), [](int a) { std::cout << a << " "; });
}

void vector_init_test() {
    std::vector<int> first = {1, 2, 3, 4};
    std::deque<int> second (first.begin(), first.end());
    int array[] = {1, 2, 3, 4};
    std::vector<int> third (std::begin(array), std::end(array));
    std::deque<int> fourth((std::istream_iterator<int>(std::cin)), std::istream_iterator<int>());

    std::vector<int> fifth(std::make_move_iterator(first.begin()), std::make_move_iterator(first.end()));

    fifth = std::move(first);
}


#include <array>
#include <cstring>

void array_init_test() {
    std::array<int, 5> arr;
    for (const auto & it : arr) 
        std::cout << it << " ";
    std::cout << std::endl;

    // 此处array 元素不能超过定义, 否则报错
    // std::array<int, 2> arr2 = {1, 2, 3};

    std::array<int, 5> arr3 ({2, 3, 4, 5, 6});
    arr3.swap(arr);

    auto begin = arr3.cend() - 1;
    std::cout << "result is " << *begin << std::endl;

    // 使用 data 函数
    std::array<char, 41> data = {};
    std::strcpy(data.data(), "hello");

    typedef std::array<std::string, 2> message_arr;
    std::cout << "tuple size is " << std::tuple_size<message_arr>::value << std::endl;
    std::tuple_element<1, message_arr>::type msg = "";
}


#include <map>
void map_insert_test() {
    std::map<std::string, int> tmp_map = {
        {"aaa", 1},
    };
    // 替换key值
    tmp_map["bbb"] = tmp_map["aaa"];
    tmp_map.erase("aaa");
    // 添加元素
    tmp_map.emplace("ccc", 2);

    // 查找元素
    auto pos = tmp_map.find("ccc");
    if (pos == tmp_map.end()) {
        std::cout << "not found" << std::endl;
    } else {
        std::cout << "found" << std::endl;
    }
}

struct MapStruct {
    int dex;
    static int map_index;
    MapStruct() {
        map_index++;
        std::cout << "map static index is " << map_index << std::endl;
    }

    // 必须重载 < 
    bool operator<(const MapStruct test) {
        return dex < test.dex;
    }
};

int MapStruct::map_index = 0;

void map_erase_test() {
    // // 
    // std::map<MapStruct, int> map_tmp = {
    //     {MapStruct{}, 2},
    // };
    // 初始化元素
    std::map<std::string, int> map_tmp = {
        {"aaa", 1},
        {"bbb", 2}
    };
    // c++11引起异常的操作
    for (auto pos = map_tmp.begin(); pos != map_tmp.end(); ++pos) {
        // 在循环中删除迭代器将会引发异常 
        if (pos->second == 2) {
            // 异常
            pos = map_tmp.erase(pos);
            // 正常
            pos = map_tmp.erase(pos);
        }
    }
    // c++11之前
    for (auto pos = map_tmp.begin(); pos != map_tmp.end(); ) {
        if (pos->second == 2) { 
            map_tmp.erase(pos++);
        } else {
            ++pos;
        }
    }

}

void map_at_test() {
    std::map<std::string, int> map_tmp;
    auto value = map_tmp["aaa"];
    std::cout << "value is " << value << std::endl;
    value = map_tmp.at("aaa");
    std::cout << "value at is " << value << std::endl;
    value = map_tmp.at("bbb");
}

void map_static_test() {
    std::map<std::string, MapStruct> map_tmp;
    map_tmp["aaa"] = MapStruct{};
}

int main() {
    

    // vector_range_test();
    // vector_size_test();
    // vector_inserter_test();
    // vector_change_test();
    // vector_alfunc_test();
    // array_init_test();
    // map_at_test();
    map_static_test();

    return 1;
}