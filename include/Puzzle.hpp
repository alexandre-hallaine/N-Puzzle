#pragma once

#include <vector>
#include <ostream>

class Puzzle {
    friend class Node;

private:
    std::vector<int> board;
    int size;

    [[nodiscard]] bool isSolvable() const;

    explicit Puzzle(const std::vector<int> &board);

public:
    explicit Puzzle(int size = 3);
    explicit Puzzle(const std::string &filename);

    [[nodiscard]] std::vector<int> getBoard() const;

    friend std::ostream &operator<<(std::ostream &os, const Puzzle &puzzle);

};
