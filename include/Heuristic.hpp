#pragma once

#include "Puzzle.hpp"

#include <string>

class Heuristic {
public:
    virtual std::string getName() = 0;
    virtual unsigned int calculate(Puzzle puzzle) = 0;
    virtual ~Heuristic() = default;
};

class MisplacedTiles : public Heuristic {
public:
    std::string getName() override;
    unsigned int calculate(Puzzle puzzle) override;
};

class ManhattanDistance : public Heuristic {
public:
    std::string getName() override;
    unsigned int calculate(Puzzle puzzle) override;
};

class LinearConflict : public ManhattanDistance {
public:
    std::string getName() override;
    unsigned int calculate(Puzzle puzzle) override;
};
