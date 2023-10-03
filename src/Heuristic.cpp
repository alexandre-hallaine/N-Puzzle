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

    unsigned int manhattanDistance = 0;
    for (std::vector<unsigned char>::size_type i = 0; i < board.size(); i++) {
        unsigned char value = board[i];
        if (value != 0) {
            unsigned char x = i % puzzle.getSize();
            unsigned char y = i / puzzle.getSize();
            unsigned char goalX = (value - 1) % puzzle.getSize();
            unsigned char goalY = (value - 1) / puzzle.getSize();
            manhattanDistance += abs(x - goalX) + abs(y - goalY);
        }
    }

    return manhattanDistance;
}

std::string LinearConflict::getName() const { return "Linear Conflict"; }
unsigned int LinearConflict::calculate(const Puzzle &puzzle) {
    std::vector<unsigned char> board = puzzle.getBoard();

    unsigned int linearConflict = 0;
    for (unsigned char i = 0; i < puzzle.getSize(); i++) {
        unsigned char max_value = 0;
        for (unsigned char j = 0; j < puzzle.getSize(); j++) {
            unsigned char value = board[i * puzzle.getSize() + j];
            if (value == 0)
                continue;

            if (value > max_value)
                max_value = value;
            else
                linearConflict++;
        }

        max_value = 0;
        for (unsigned char j = 0; j < puzzle.getSize(); j++) {
            unsigned char value = board[j * puzzle.getSize() + i];
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
