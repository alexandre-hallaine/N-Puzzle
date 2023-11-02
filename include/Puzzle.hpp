#pragma once

#include <vector>
#include <utility>
#include <memory>
#include <string>
#include <ostream>

class Puzzle {
private:

    int size;
    std::vector<int> board;
    std::pair<int, int> emptyTile;

    enum Direction {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    explicit Puzzle(std::vector<int> board);

    [[nodiscard]] std::unique_ptr<Puzzle> getSpecificChildren(Direction direction) const;
    [[nodiscard]] bool isSolvable() const;

public:
    explicit Puzzle(int size = 3);
    explicit Puzzle(const std::string &filename);

    [[nodiscard]] int getSize() const;
    [[nodiscard]] std::vector<int> getBoard() const;
    [[nodiscard]] std::vector<Puzzle> getChildren() const;

    bool operator==(const Puzzle &other) const;
    friend std::ostream &operator<<(std::ostream &os, const Puzzle &puzzle);
};
