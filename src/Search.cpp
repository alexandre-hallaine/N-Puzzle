#include "Search.hpp"

#include <iostream>
#include <algorithm>

template<typename NodeComparator>
std::stack<Puzzle> Search<NodeComparator>::reconstructPath(const Node *node) {
    if (node == nullptr)
        return {};
    std::stack<Puzzle> path = reconstructPath(node->getParent());
    path.push(node->getPuzzle());
    return path;
}

template<typename NodeComparator>
Search<NodeComparator>::Search(const std::shared_ptr<Heuristic> &heuristic) : heuristic(heuristic) {
}

template<typename NodeComparator>
std::unique_ptr<std::stack<Puzzle>> Search<NodeComparator>::solve(Puzzle puzzle) {
    while (!frontier.empty())
        frontier.pop();
    visited.clear();

    frontier.push(std::make_shared<Node>(puzzle, *heuristic));
    while (!frontier.empty()) {
        std::shared_ptr<Node> node = frontier.top();
        frontier.pop();

        if (node->getHeuristic() == 0)
            return std::make_unique<std::stack<Puzzle>>(reconstructPath(node.get()));

        const Puzzle &puzzle = node->getPuzzle();
        visited.insert(puzzle.getBoard());
        for (const Puzzle &child: puzzle.getChildren())
            if (visited.find(child.getBoard()) == visited.end())
                frontier.push(std::make_shared<Node>(child, *heuristic, node));
    }

    return nullptr;
}

template<typename NodeComparator>
void Search<NodeComparator>::printStats() {
    std::cout << "Complexity in time: " << frontier.size() << std::endl;
    std::cout << "Complexity in size: " << visited.size() << std::endl;
}
