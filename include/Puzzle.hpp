#pragma once

#include <vector>
#include <ostream>

namespace NPuzzle {
    class Puzzle {
        friend class Node;

    private:
        std::vector<int> board;
        int size = 0;

        explicit Puzzle(const std::vector<int> &board);

        [[nodiscard]] bool isSolvable() const;

    public:
        explicit Puzzle(int size = 3);
        explicit Puzzle(const std::string &filename);

        friend std::ostream &operator<<(std::ostream &os, const Puzzle &puzzle);
    };
}
