#include "Heuristic.hpp"

#include <cmath>

namespace NPuzzle {
    int Heuristic_MisplacedTiles::calculate(const std::vector<int> &board, int /* size */) {
        int misplacedTiles = 0;
        for (size_t i = 0, len = board.size(); i < len; ++i)
            misplacedTiles += board[i] != 0 && board[i] != static_cast<int>(i) + 1;
        return misplacedTiles;
    }

    int Heuristic_ManhattanDistance::calculate(const std::vector<int> &board, int size) {
        int manhattanDistance = 0;
        for (size_t i = 0, len = board.size(); i < len; ++i)
            if (board[i] != 0) {
                int tile = board[i] - 1;
                manhattanDistance += std::abs(static_cast<int>(tile % size) - static_cast<int>(i % size)) +
                                     std::abs(static_cast<int>(tile / size) - static_cast<int>(i / size));
            }
        return manhattanDistance;
    }

    int Heuristic_LinearConflict::calculate(const std::vector<int> &board, int size) {
        int linearConflict = 0;
        int manhattanDistance = Heuristic_ManhattanDistance::calculate(board, size);

        for (int row = 0; row < size; ++row)
            for (int col = 0; col < size; ++col) {
                int index = row * size + col;
                int tile = board[index];
                if (tile != 0) {
                    int goalRow = (tile - 1) / size;
                    int goalCol = (tile - 1) % size;

                    if (goalRow == row)
                        for (int k = col + 1; k < size; ++k) {
                            int otherTile = board[row * size + k];
                            if (otherTile != 0 && (otherTile - 1) / size == row && tile > otherTile)
                                linearConflict++;
                        }
                    if (goalCol == col)
                        for (int k = row + 1; k < size; ++k) {
                            int otherTile = board[k * size + col];
                            if (otherTile != 0 && (otherTile - 1) % size == col && tile > otherTile)
                                linearConflict++;
                        }
                }
            }

        return manhattanDistance + 2 * linearConflict;
    }
}
