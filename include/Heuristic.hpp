#pragma once

#include "Puzzle.hpp"

#include <string>

class Heuristic {
public:
    virtual ~Heuristic() = default;

    virtual unsigned int calculate(const Puzzle &puzzle) = 0;
};

class MisplacedTiles : public Heuristic {
public:
    unsigned int calculate(const Puzzle &puzzle) override;
};

class ManhattanDistance : public Heuristic {
public:
    unsigned int calculate(const Puzzle &puzzle) override;
};

class LinearConflict : public ManhattanDistance {
public:
    unsigned int calculate(const Puzzle &puzzle) override;
};
