#include "Heuristic.hpp"

std::string MisplacedTiles::getName() const { return "Misplaced Tiles"; }
unsigned int MisplacedTiles::calculate(const Puzzle &puzzle) {
    std::vector<unsigned char> board = puzzle.getBoard();

    unsigned int misplacedTiles = 0;
    for (std::vector<unsigned char>::size_type i = 0; i < board.size(); i++)
        if (board[i] != i + 1)
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
            manhattanDistance += abs(x - goalX) + abs(y - goalY);
        }
    }

    return manhattanDistance;
}

std::string LinearConflict::getName() const { return "Linear Conflict"; }
unsigned int LinearConflict::calculate(const Puzzle &puzzle) {
    std::vector<unsigned char> board = puzzle.getBoard();
    unsigned char size = puzzle.getSize();

    unsigned int linearConflict = 0;
    for (unsigned char i = 0; i < size; i++) {
        unsigned char max_value = 0;
        for (unsigned char j = 0; j < size; j++) {
            unsigned char value = board[i * size + j];
            if (value == 0)
                continue;

            if (value > max_value)
                max_value = value;
            else
                linearConflict++;
        }

        max_value = 0;
        for (unsigned char j = 0; j < size; j++) {
            unsigned char value = board[j * size + i];
            if (value == 0)
                continue;

            if (value > max_value)
                max_value = value;
            else
                linearConflict++;
        }
    }

    return ManhattanDistance::calculate(puzzle) + 2 * linearConflict;
}
