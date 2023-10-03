#pragma once

#include "Puzzle.hpp"

#include <string>

class Heuristic {
public:
    [[nodiscard]] virtual std::string getName() const = 0;
    virtual unsigned int calculate(const Puzzle &puzzle) = 0;
    virtual ~Heuristic() = default;
};

class MisplacedTiles : public Heuristic {
public:
    [[nodiscard]] std::string getName() const override;
    unsigned int calculate(const Puzzle &puzzle) override;
};

class ManhattanDistance : public Heuristic {
public:
    [[nodiscard]] std::string getName() const override;
    unsigned int calculate(const Puzzle &puzzle) override;
};

class LinearConflict : public ManhattanDistance {
public:
    [[nodiscard]] std::string getName() const override;
    unsigned int calculate(const Puzzle &puzzle) override;
};
