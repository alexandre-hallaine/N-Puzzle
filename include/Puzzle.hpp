#pragma once

#include <vector>
#include <ostream>

class Puzzle {
    template<typename T> friend
    class Search;

private:
    std::vector<int> board;

    [[nodiscard]] bool isSolvable() const;

    explicit Puzzle(const std::vector<int> &board);

public:
    explicit Puzzle(int size = 3);
    explicit Puzzle(const std::string &filename);

    [[nodiscard]] std::vector<int> getBoard() const;

    friend std::ostream &operator<<(std::ostream &os, const Puzzle &puzzle);

};
