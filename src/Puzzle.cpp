#include "Puzzle.hpp"

#include <algorithm>
#include <random>
#include <fstream>
#include <iterator>

namespace NPuzzle {
    int countInversions(const std::vector<int> &board) {
        int inversions = 0;
        for (size_t i = 0; i < board.size(); ++i)
            for (size_t j = i + 1; j < board.size(); ++j)
                if (board[i] > board[j] && board[i] != 0 && board[j] != 0)
                    ++inversions;
        return inversions;
    }

    Puzzle::Puzzle(const std::vector<int> &initialBoard)
            : board(initialBoard), size(static_cast<int>(std::sqrt(board.size()))) {
        if (size * size != static_cast<int>(board.size()))
            throw std::invalid_argument("Board size must be a perfect square.");
    }

    bool Puzzle::isSolvable() const {
        int inversions = countInversions(board);
        if (size % 2 != 0)
            return inversions % 2 == 0;
        else {
            size_t zeroRow = (std::find(board.begin(), board.end(), 0) - board.begin()) / size;
            return (zeroRow % 2 == 0) == (inversions % 2 != 0);
        }
    }

    Puzzle::Puzzle(int dimension) : size(dimension) {
        if (dimension <= 0)
            throw std::invalid_argument("Dimension must be positive.");

        board.resize(size * size);
        std::iota(board.begin(), board.end(), 1);
        board.back() = 0;

        static std::mt19937 g(std::random_device{}());
        do {
            std::shuffle(board.begin(), board.end(), g);
        } while (!isSolvable());
    }

    Puzzle::Puzzle(const std::string &filename) {
        std::ifstream file(filename);
        if (!file)
            throw std::runtime_error("Could not open file: " + filename);

        file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        file >> size;

        if (size <= 0)
            throw std::runtime_error("Board size must be positive.");

        board.reserve(size * size);
        std::copy_n(std::istream_iterator<int>(file), size * size, std::back_inserter(board));

        if (board.size() != static_cast<size_t>(size) * static_cast<size_t>(size))
            throw std::runtime_error("Board size does not match the expected size.");

        if (!isSolvable())
            throw std::runtime_error("Board is not solvable.");
    }

    std::ostream &operator<<(std::ostream &os, const Puzzle &puzzle) {
        for (int i = 0; i < puzzle.size; ++i)
            for (int j = 0; j < puzzle.size; ++j) {
                if (j > 0) os << '\t';
                else if (i > 0) os << '\n';
                if (puzzle.board[i * puzzle.size + j] == 0) os << '_';
                else os << puzzle.board[i * puzzle.size + j];
            }
        return os;
    }
}
