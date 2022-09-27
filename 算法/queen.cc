#include <algorithm>
#include <vector>
#include <iostream>

using ChessLine = std::vector<int>;
using ChessBoard = std::vector<ChessLine>;


bool is_pos_valid(ChessBoard& board, int row, int col) {
    // check line 
    for (int index = 0; index < board[row].size(); index++) {
        if (board[row][index] == 1) 
            return false;
    }

    // check col
    for (int index = 0; index < row; index++) {
        if (board[index][col] == 1)
            return false;
    }

    // left 45
    for (int index = row, jdex = col; index >= 0 && jdex >=0; index--, jdex--) {
        if (board[index][jdex] == 1)
            return false;
    }

    // right 45
    for (int index = row, jdex = col; index >= 0 && jdex < board[0].size(); index--, jdex++) {
        if (board[index][jdex] == 1)
            return false;
    }    
    return true;
}

std::vector<ChessBoard> results;
void backtrace(ChessBoard& board, int row) {
    if (board.size() == row) {
        results.push_back(board);
        return;
    }
    
    for (int index = 0; index < board[row].size(); index++) {
        if (!is_pos_valid(board, row, index))
            continue;
        board[row][index] = 1;
        backtrace(board, row + 1);
        board[row][index] = 0;
    }
}

int main() {
    results.clear();
    ChessBoard board(8, ChessLine(8, 0));
    backtrace(board, 0);

    for (const auto& rboard : results) {
        for (const auto& rline : rboard) {
            for (const auto& elem : rline)
                std::cout << elem << " ";
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    std::cout << "total solution: " << results.size() << std::endl;
    return 0;
}