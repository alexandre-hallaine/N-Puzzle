#pragma once

#include "Puzzle.hpp"
#include "Heuristic.hpp"

class Node {
private:
    Puzzle puzzle;
    Node *parent;

    unsigned int cost;
    unsigned int heuristic;

public:
    Node(const Puzzle &puzzle, Heuristic *heuristic, Node *parent = nullptr);

    Puzzle &getPuzzle();
    Node *getParent();

    [[nodiscard]] unsigned int getCost() const;
    [[nodiscard]] unsigned int getHeuristic() const;
    [[nodiscard]] unsigned int getScore() const;
};

struct NodeComparator {
    virtual bool operator()(const std::shared_ptr<Node> &lhs, const std::shared_ptr<Node> &rhs) const = 0;
};

struct AStarComparator : public NodeComparator {
    bool operator()(const std::shared_ptr<Node> &lhs, const std::shared_ptr<Node> &rhs) const override;
};

struct GreedyComparator : public NodeComparator {
    bool operator()(const std::shared_ptr<Node> &lhs, const std::shared_ptr<Node> &rhs) const override;
};

struct UniformCostComparator : public NodeComparator {
    bool operator()(const std::shared_ptr<Node> &lhs, const std::shared_ptr<Node> &rhs) const override;
};
