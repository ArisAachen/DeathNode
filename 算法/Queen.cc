#include <utility>
#include <vector>
#include <string>
#include <iostream>

using namespace std;




std::vector<std::vector<std::string>> results;


bool is_valid(int row, int col, std::vector<std::string>& chessboard) {
    // 判断列
    for (int index = 0; index < row; index ++) {
        if (chessboard[index][col] == 'Q') 
            return false;
    }
    // 判断 45度角
    for (int index = row -1, jndex = col - 1; index >=0 
        && jndex >=0; index--, jndex--) {
        if (chessboard[index][jndex] == 'Q') 
            return false;
    }
    // 判断 135度角
    for (int index = row -1, jndex = col + 1; index >=0 
        && jndex <= chessboard.size(); index--, jndex++) {
        if (chessboard[index][jndex] == 'Q') 
            return false;
    }
    return true;
}


void back_trace(int row, std::vector<std::string>& chessboard) {
    if (row == chessboard.size()) {
        results.push_back(chessboard);
        return;
    }
    // 路径
    for (int col = 0; col < chessboard.size(); col++) {
        if (is_valid(row, col, chessboard)) {
            chessboard[row][col] = 'Q';
            back_trace(row + 1, chessboard);
            chessboard[row][col] = '.';
        }
    }
}

int main() {
    results.clear();
    std::vector<std::string> chessboard(8, std::string(8, '.'));
    back_trace(0, chessboard);
    std::cout << "solution count: " << results.size() << std::endl; 
    for (const auto& result : results) {
        for (const auto& elem : result) {
            cout << elem << endl;
        }
        std::cout << "============" << std::endl << std::endl;
    }
    return 0;
}



class Solution {
private:
vector<vector<string>> result;
// n 为输入的棋盘大小
// row 是当前递归到棋盘的第几行了
void backtracking(int n, int row, vector<string>& chessboard) {
    if (row == n) {
        result.push_back(chessboard);
        return;
    }
    for (int col = 0; col < n; col++) {
        if (isValid(row, col, chessboard, n)) { // 验证合法就可以放
            chessboard[row][col] = 'Q'; // 放置皇后
            backtracking(n, row + 1, chessboard);
            chessboard[row][col] = '.'; // 回溯，撤销皇后
        }
    }
}
bool isValid(int row, int col, vector<string>& chessboard, int n) {
    // 检查列
    for (int i = 0; i < row; i++) { // 这是一个剪枝
        if (chessboard[i][col] == 'Q') {
            return false;
        }
    }
    // 检查 45度角是否有皇后
    for (int i = row - 1, j = col - 1; i >=0 && j >= 0; i--, j--) {
        if (chessboard[i][j] == 'Q') {
            return false;
        }
    }
    // 检查 135度角是否有皇后
    for(int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
        if (chessboard[i][j] == 'Q') {
            return false;
        }
    }
    return true;
}
public:
    vector<vector<string>> solveNQueens(int n) {
        result.clear();
        std::vector<std::string> chessboard(n, std::string(n, '.'));
        backtracking(n, 0, chessboard);
        return result;
    }
};

