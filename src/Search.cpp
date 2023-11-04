#include "Search.hpp"

#include <iostream>

namespace NPuzzle {
    template<typename NodeComparator>
    std::stack<Puzzle> Search<NodeComparator>::reconstructPath(const std::shared_ptr<Node> &node) {
        std::stack<Puzzle> path;
        for (auto current = node; current != nullptr; current = current->getParent())
            path.push(current->getPuzzle());
        return path;
    }

    template<typename NodeComparator>
    std::unique_ptr<std::stack<Puzzle>>
    Search<NodeComparator>::solve(const Puzzle &puzzle, const std::shared_ptr<Heuristic> &heuristic) {
        auto root = std::make_shared<Node>(puzzle, heuristic);
        frontier = decltype(frontier)();
        frontier.emplace(root);

        visited.clear();

        std::vector<std::shared_ptr<Node>> successors;
        successors.reserve(4);

        while (!frontier.empty()) {
            auto node = frontier.top();
            frontier.pop();

            if (!visited.insert(node->getBoard()).second) continue;

            if (node->getHeuristic() == 0)
                return std::make_unique<std::stack<Puzzle>>(reconstructPath(node));

            node->getSuccessors(node, successors);
            for (auto &child: successors)
                frontier.emplace(std::move(child));
            successors.clear();
        }

        return nullptr;
    }

    template<typename NodeComparator>
    void Search<NodeComparator>::printStats() {
        std::cout << "Complexity in time: " << frontier.size() << std::endl;
        std::cout << "Complexity in size: " << visited.size() << std::endl;
    }
}
