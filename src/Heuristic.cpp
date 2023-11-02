#include "Heuristic.hpp"

#include <cmath>

std::string MisplacedTiles::getName() const { return "Misplaced Tiles"; }
unsigned int MisplacedTiles::calculate(const Puzzle &puzzle) {
    std::vector<unsigned char> board = puzzle.getBoard();

    unsigned int misplacedTiles = 0;
    for (std::vector<unsigned char>::size_type i = 0; i < board.size(); i++)
        if (board[i] != 0 && board[i] != i + 1)
            misplacedTiles++;

    return misplacedTiles;
}

std::string ManhattanDistance::getName() const { return "Manhattan Distance"; }
unsigned int ManhattanDistance::calculate(const Puzzle &puzzle) {
    std::vector<unsigned char> board = puzzle.getBoard();
    unsigned char size = puzzle.getSize();

    unsigned int manhattanDistance = 0;
    for (std::vector<unsigned char>::size_type i = 0; i < board.size(); i++) {
        unsigned char value = board[i];
        if (value != 0) {
            unsigned char x = i % size;
            unsigned char y = i / size;
            unsigned char goalX = (value - 1) % size;
            unsigned char goalY = (value - 1) / size;
            manhattanDistance += std::abs(x - goalX) + std::abs(y - goalY);
        }
    }

    return manhattanDistance;
}

std::string LinearConflict::getName() const { return "Linear Conflict"; }
unsigned int LinearConflict::calculate(const Puzzle &puzzle) {
    std::vector<unsigned char> board = puzzle.getBoard();
    unsigned char size = puzzle.getSize();

    unsigned int linearConflict = 0;
    for (unsigned char i = 0; i < size; ++i) // For each row and column
    {
        for (unsigned char j = 0; j < size - 1; ++j) // For each pair in the row/column
        {
            unsigned char value_row = board[i * size + j];
            unsigned char value_col = board[j * size + i];
            for (unsigned char k = j + 1; k < size; ++k) // Compare with subsequent tiles
            {
                unsigned char other_value_row = board[i * size + k];
                unsigned char other_value_col = board[k * size + i];

                // Check if value_row is in its goal row and there is a tile that should come after it
                if (value_row != 0 && (value_row - 1) / size == i && other_value_row != 0 &&
                    (other_value_row - 1) / size == i && value_row > other_value_row) {
                    linearConflict++;
                }

                // Check if value_col is in its goal column and there is a tile that should come after it
                if (value_col != 0 && (value_col - 1) % size == i && other_value_col != 0 &&
                    (other_value_col - 1) % size == i && value_col > other_value_col) {
                    linearConflict++;
                }
            }
        }
    }

    // Each conflict accounts for 2 additional moves
    return ManhattanDistance::calculate(puzzle) + 2 * linearConflict;
}
