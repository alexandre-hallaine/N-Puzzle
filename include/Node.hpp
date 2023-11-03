#pragma once

#include "Heuristic.hpp"
#include "Puzzle.hpp"

#include <memory>

class Node {
    template<typename T> friend
    class Search;

private:
    const std::vector<int> board;
    const std::shared_ptr<Node> parent;
    const std::shared_ptr<Heuristic> heuristic;

    int cost_value = 0;
    int heuristic_value = 0;
    int size;

    Node(const std::vector<int> &board, int size, const std::shared_ptr<Heuristic> &heuristic,
         const std::shared_ptr<Node> &parent);

    Node(const Puzzle &puzzle, const std::shared_ptr<Heuristic> &heuristic);

public:

    [[nodiscard]] const std::shared_ptr<Node> &getParent() const;
    [[nodiscard]] const std::vector<int> &getBoard() const;
    [[nodiscard]] std::vector<std::shared_ptr<Node>> getSuccessors() const;

    [[nodiscard]] int getCost() const;
    [[nodiscard]] int getHeuristic() const;
    [[nodiscard]] int getScore() const;

    [[nodiscard]] Puzzle getPuzzle() const;
};

struct NodeComparator {
    virtual bool operator()(const std::shared_ptr<Node> &lhs, const std::shared_ptr<Node> &rhs) const = 0;
};

struct AStarComparator : public NodeComparator {
    [[nodiscard]]  bool operator()(const std::shared_ptr<Node> &lhs, const std::shared_ptr<Node> &rhs) const override;
};

struct GreedyComparator : public NodeComparator {
    [[nodiscard]] bool operator()(const std::shared_ptr<Node> &lhs, const std::shared_ptr<Node> &rhs) const override;
};

struct UniformCostComparator : public NodeComparator {
    [[nodiscard]] bool operator()(const std::shared_ptr<Node> &lhs, const std::shared_ptr<Node> &rhs) const override;
};
