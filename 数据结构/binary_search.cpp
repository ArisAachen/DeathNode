#include <optional>

struct Elements {
    int* addr;
    int length;
};

std::optional<int> binary_search(Elements& elems, int target) {
    int head = 0, tail = elems.length;
    
    while (head <= tail) {
        int mid = (head + tail) / 2;
        if (mid > target)
            tail = mid - 1;
        else if (mid < target) 
            head = mid + 1;
        else
            return mid;
    }
    return std::nullopt;
}