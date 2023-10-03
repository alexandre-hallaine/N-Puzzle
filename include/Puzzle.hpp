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

    explicit Puzzle(std::vector<unsigned char> board);

    [[nodiscard]] std::unique_ptr<Puzzle> getSpecificChildren(Direction direction) const;
    [[nodiscard]] bool isSolvable() const;

public:
    explicit Puzzle(unsigned char size = 3);
    explicit Puzzle(const std::string &filename);

    [[nodiscard]] unsigned char getSize() const;
    [[nodiscard]] std::vector<unsigned char> getBoard() const;
    [[nodiscard]] std::vector<Puzzle> getChildren() const;

    bool operator==(const Puzzle &other) const;
    friend std::ostream &operator<<(std::ostream &os, const Puzzle &puzzle);
};
