#include "Puzzle.hpp"

#include <numeric>
#include <algorithm>
#include <cmath>
#include <random>
#include <fstream>

Puzzle::Puzzle(const std::vector<int> &board) : board(board), size((int) std::sqrt(board.size())) {}

bool Puzzle::isSolvable() const {
    int inversions = 0;
    for (auto it = board.begin(); it != board.end(); it++)
        if (*it != 0)
            inversions += (int) std::count_if(it + 1, board.end(), [it](int x) { return x != 0 && *it > x; });

    auto zeroIndex = std::distance(board.begin(), std::find(board.begin(), board.end(), 0));
    std::pair<int, int> zero = {zeroIndex / size, zeroIndex % size};

    if (size % 2 == 0)
        inversions += zero.first + 1;
    return inversions % 2 == 0;
}

Puzzle::Puzzle(int size) : board(size * size), size(size) {
    std::iota(board.begin(), board.end(), 1);
    board.back() = 0;

    std::random_device rd;
    std::mt19937 g(rd());
    do {
        std::shuffle(board.begin(), board.end(), g);
    } while (!isSolvable());
}

Puzzle::Puzzle(const std::string &filename) : size(0) {
    std::ifstream file(filename);
    if (!file)
        throw std::runtime_error("Could not open file " + filename);
    file.exceptions(std::ifstream::badbit);

    file >> size;
    if (!file)
        throw std::runtime_error("Invalid file format: could not read size");

    int number;
    while (file >> number) {
        board.push_back(number);
    }

    if ((int) board.size() != size * size)
        throw std::runtime_error("Board size does not match size");
    if (!isSolvable())
        throw std::runtime_error("Board is not solvable");
}

std::vector<int> Puzzle::getBoard() const { return board; }

std::ostream &operator<<(std::ostream &os, const Puzzle &puzzle) {
    for (int i = 0; i < puzzle.size; ++i) {
        for (int j = 0; j < puzzle.size; ++j) {
            if (j > 0) os << "\t";
            else if (i > 0) os << std::endl;
            if (puzzle.board[i * puzzle.size + j] == 0) os << '_';
            else os << puzzle.board[i * puzzle.size + j];
        }
    }
    return os;
}
