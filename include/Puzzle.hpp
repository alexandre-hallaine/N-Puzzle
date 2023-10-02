#pragma once

#include <vector>
#include <utility>
#include <memory>
#include <string>
#include <ostream>

class Puzzle {
private:
    unsigned char size;
    std::vector<unsigned char> board;
    std::pair<unsigned char, unsigned char> emptyTile;

    enum Direction {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    std::unique_ptr<Puzzle> move(Direction direction);
    bool isSolvable();

public:
    explicit Puzzle(unsigned char size = 3);
    explicit Puzzle(const std::string &filename);
    explicit Puzzle(std::vector<unsigned char> board);

    [[nodiscard]] unsigned char getSize() const;
    std::vector<unsigned char> getBoard();
    std::vector<Puzzle> getChildren();

    bool operator==(const Puzzle &other) const;
    friend std::ostream &operator<<(std::ostream &os, const Puzzle &puzzle);
};
