#pragma once

#include "Heuristic.hpp"
#include "Puzzle.hpp"

#include <memory>

namespace NPuzzle {
    class Node {
    private:
        std::shared_ptr<Heuristic> heuristic = nullptr;
        const std::shared_ptr<Node> parent = nullptr;
        const std::vector<int> board;
        int size = 0;

        int cost_value = 0;
        int heuristic_value = 0;

    public:
        Node(const Puzzle &puzzle, const std::shared_ptr<Heuristic> &heuristic);
        Node(std::vector<int> board, std::shared_ptr<Node> parent);

        [[nodiscard]] int getCost() const;
        [[nodiscard]] int getHeuristic() const;
        [[nodiscard]] int getScore() const;

        [[nodiscard]] const std::shared_ptr<Node> &getParent() const;
        [[nodiscard]] const std::vector<int> &getBoard() const;
        [[nodiscard]] Puzzle getPuzzle() const;

        void getSuccessors(std::shared_ptr<Node> &me, std::vector<std::shared_ptr<Node>> &successors) const;
    };

    struct NodeComparator {
        virtual bool operator()(const std::shared_ptr<Node> &lhs, const std::shared_ptr<Node> &rhs) const = 0;
    };

    struct NodeComparator_AStar : public NodeComparator {
        [[nodiscard]]  bool
        operator()(const std::shared_ptr<Node> &lhs, const std::shared_ptr<Node> &rhs) const override;
    };

    struct NodeComparator_Greedy : public NodeComparator {
        [[nodiscard]] bool
        operator()(const std::shared_ptr<Node> &lhs, const std::shared_ptr<Node> &rhs) const override;
    };

    struct NodeComparator_UniformCost : public NodeComparator {
        [[nodiscard]] bool
        operator()(const std::shared_ptr<Node> &lhs, const std::shared_ptr<Node> &rhs) const override;
    };
}
