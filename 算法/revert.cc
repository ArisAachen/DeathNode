#include <vector>

int revert(int origin) {
  std::vector<int> storage;

  int left = origin;
  while (left > 10) {
    int top = left % 10;
    storage.push_back(top);
    left = left / 10;
  }

  int result = left;
  while (!storage.empty()) {
    int top = storage.back();
    storage.pop_back();
    result += 10 * top;
  }

  return 0;
}

int main (int argc, char *argv[])
{
  
  return 0;
}
