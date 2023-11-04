#pragma once

#include <vector>

namespace NPuzzle {
    class Heuristic {
    public:
        virtual ~Heuristic() = default;

        virtual int calculate(const std::vector<int> &board, int size) = 0;
    };

    class Heuristic_MisplacedTiles : public Heuristic {
    public:
        [[nodiscard]] int calculate(const std::vector<int> &board, int size) override;
    };

    class Heuristic_ManhattanDistance : public Heuristic {
    public:
        [[nodiscard]] int calculate(const std::vector<int> &board, int size) override;
    };

    class Heuristic_LinearConflict : public Heuristic_ManhattanDistance {
    public:
        [[nodiscard]] int calculate(const std::vector<int> &board, int size) override;
    };
}
