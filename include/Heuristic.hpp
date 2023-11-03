#pragma once

#include <vector>

class Heuristic {
public:
    virtual ~Heuristic() = default;

    virtual int calculate(const std::vector<int> &board, int size) = 0;
};

class MisplacedTiles : public Heuristic {
public:
    [[nodiscard]] int calculate(const std::vector<int> &board, int size) override;
};

class ManhattanDistance : public Heuristic {
public:
    [[nodiscard]] int calculate(const std::vector<int> &board, int size) override;
};

class LinearConflict : public ManhattanDistance {
public:
    [[nodiscard]] int calculate(const std::vector<int> &board, int size) override;
};
