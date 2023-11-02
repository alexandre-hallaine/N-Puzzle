#include "Heuristic.hpp"

#include <cmath>

unsigned int MisplacedTiles::calculate(const Puzzle &puzzle) {
    std::vector<int> board = puzzle.getBoard();

    unsigned int misplacedTiles = 0;
    for (std::vector<int>::size_type i = 0; i < board.size(); i++)
        if (board[i] != 0 && board[i] != (int) (i + 1))
            misplacedTiles++;

    return misplacedTiles;
}

unsigned int ManhattanDistance::calculate(const Puzzle &puzzle) {
    std::vector<int> board = puzzle.getBoard();
    int size = puzzle.getSize();

    unsigned int manhattanDistance = 0;
    for (std::vector<int>::size_type i = 0; i < board.size(); i++) {
        int value = board[i];
        if (value != 0) {
            int x = i % size;
            int y = i / size;
            int goalX = (value - 1) % size;
            int goalY = (value - 1) / size;
            manhattanDistance += std::abs(x - goalX) + std::abs(y - goalY);
        }
    }

    return manhattanDistance;
}

unsigned int LinearConflict::calculate(const Puzzle &puzzle) {
    std::vector<int> board = puzzle.getBoard();
    int size = puzzle.getSize();

    unsigned int linearConflict = 0;
    for (int i = 0; i < size; ++i) // For each row and column
    {
        for (int j = 0; j < size - 1; ++j) // For each pair in the row/column
        {
            int value_row = board[i * size + j];
            int value_col = board[j * size + i];
            for (int k = j + 1; k < size; ++k) // Compare with subsequent tiles
            {
                int other_value_row = board[i * size + k];
                int other_value_col = board[k * size + i];

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
