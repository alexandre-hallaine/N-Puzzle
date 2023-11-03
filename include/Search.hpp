#pragma once

#include "Heuristic.hpp"
#include "Node.hpp"

#include <queue>
#include <unordered_set>
#include <stack>

class SearchBase {
public:
    virtual ~SearchBase() = default;

    virtual std::unique_ptr<std::stack<Puzzle>> solve(const Puzzle &puzzle) = 0;
    virtual void printStats() = 0;
};

template<typename NodeComparator = AStarComparator>
class Search : public SearchBase {
private:
    struct VectorHash {
        size_t operator()(const std::vector<int> &v) const {
            std::hash<int> hasher;
            size_t seed = 0;
            for (int i: v) {
                // Combine the hash of the current element with the
                // running total using a bitwise XOR and bit shifting to
                // reduce the chance of collisions.
                seed ^= hasher(i) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
            return seed;
        }
    };

    std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node>>, NodeComparator> frontier;
    std::unordered_set<std::vector<int>, VectorHash> visited;

    std::shared_ptr<Heuristic> heuristic;

    std::stack<Puzzle> reconstructPath(const std::shared_ptr<Node> &node);

public:
    explicit Search(const std::shared_ptr<Heuristic> &heuristic);

    [[nodiscard]] std::unique_ptr<std::stack<Puzzle>> solve(const Puzzle &puzzle) override;
    void printStats() override;
};

template
class Search<AStarComparator>;

template
class Search<GreedyComparator>;

template
class Search<UniformCostComparator>;
