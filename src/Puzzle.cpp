#include "Puzzle.hpp"

#include <numeric>
#include <random>
#include <fstream>
#include <cmath>

Puzzle::Puzzle(std::vector<unsigned char> board) : size((unsigned char) std::sqrt(board.size())), board(board) {
    if (!isSolvable())
        throw std::runtime_error("Board is not solvable");

    for (auto i = 0; i < board.size(); i++)
        if (board[i] == 0) {
            emptyTile = std::make_pair(i / size, i % size);
            break;
        }
}

std::unique_ptr<Puzzle> Puzzle::getSpecificChildren(Direction direction) const {
    Puzzle puzzle = *this;

    switch (direction) {
        case UP:
            if (puzzle.emptyTile.first != 0)
                puzzle.emptyTile.first--;
            break;
        case DOWN:
            if (puzzle.emptyTile.first != puzzle.size - 1)
                puzzle.emptyTile.first++;
            break;
        case LEFT:
            if (puzzle.emptyTile.second != 0)
                puzzle.emptyTile.second--;
            break;
        case RIGHT:
            if (puzzle.emptyTile.second != puzzle.size - 1)
                puzzle.emptyTile.second++;
            break;
    }
    if (puzzle.emptyTile == emptyTile)
        return nullptr;

    std::swap(puzzle.board[puzzle.emptyTile.first * puzzle.size + puzzle.emptyTile.second],
              puzzle.board[emptyTile.first * size + emptyTile.second]);
    return std::make_unique<Puzzle>(puzzle);
}

bool Puzzle::isSolvable() const {
    size_t inversions = 0;
    for (auto i = 0; i < board.size(); i++)
        for (auto j = i + 1; j < board.size(); j++)
            if (board[i] != 0 && board[j] != 0 && board[i] > board[j])
                inversions++;

    if (size % 2 != 1)
        inversions += emptyTile.first;
    return inversions % 2 == 0;
}

Puzzle::Puzzle(unsigned char size) : size(size) {
    std::vector<unsigned char> board_new(size * size);
    std::iota(board_new.begin(), board_new.end(), 1);
    board_new.back() = 0;

    *this = Puzzle(board_new);

    std::random_device rd;
    std::mt19937 g(rd());

    for (auto _ = 0; _ < 100 * board.size(); _++) {
        std::vector<Puzzle> children = getChildren();
        std::uniform_int_distribution<std::vector<Puzzle>::size_type> d(0, children.size() - 1);
        *this = children[d(g)];
    }
}

Puzzle::Puzzle(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Could not open file " + filename);

    int number;
    file >> number;
    size = number;

    while (file >> number)
        board.push_back(number);

    if (board.size() != size * size)
        throw std::runtime_error("Board size does not match size");

    *this = Puzzle(board);
}

unsigned char Puzzle::getSize() const { return size; }
std::vector<unsigned char> Puzzle::getBoard() const { return board; }
std::vector<Puzzle> Puzzle::getChildren() const {
    std::vector<Puzzle> children;
    for (Direction direction: {UP, DOWN, LEFT, RIGHT}) {
        std::unique_ptr<Puzzle> child = getSpecificChildren(direction);
        if (child)
            children.push_back(*child);
    }
    return children;
}

bool Puzzle::operator==(const Puzzle &other) const { return board == other.board; }
std::ostream &operator<<(std::ostream &os, const Puzzle &puzzle) {
    for (auto i = 0; i < puzzle.board.size(); i++) {
        if (i % puzzle.size != 0)
            os << "\t";
        else if (i != 0)
            os << std::endl;

        os << (int) puzzle.board[i];
    }

    return os;
}
