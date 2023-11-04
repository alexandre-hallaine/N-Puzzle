#include "Node.hpp"

#include <algorithm>

namespace NPuzzle {
    Node::Node(const Puzzle &puzzle, const std::shared_ptr<Heuristic> &heuristic)
            : heuristic(heuristic), board(puzzle.board), size(puzzle.size),
              heuristic_value(heuristic ? heuristic->calculate(puzzle.board, puzzle.size) : 0) {
        if (!heuristic) {
            throw std::invalid_argument("Heuristic cannot be null");
        }
    }

    Node::Node(std::vector<int> board, std::shared_ptr<Node> parent)
            : heuristic(parent ? parent->heuristic : nullptr),
              parent(std::move(parent)),
              board(std::move(board)),
              size(this->parent ? this->parent->size : 0),
              cost_value(this->parent ? this->parent->cost_value + 1 : 0),
              heuristic_value(
                      this->parent && this->heuristic ? this->heuristic->calculate(this->board, this->size) : 0) {
    }

    int Node::getCost() const { return cost_value; }

    int Node::getHeuristic() const { return heuristic_value; }

    int Node::getScore() const { return cost_value + heuristic_value; }

    const std::shared_ptr<Node> &Node::getParent() const { return parent; }

    const std::vector<int> &Node::getBoard() const { return board; }

    Puzzle Node::getPuzzle() const { return Puzzle(board); }

    void Node::getSuccessors(std::shared_ptr<Node> &me, std::vector<std::shared_ptr<Node>> &successors) const {
        size_t zeroIndex = std::distance(board.begin(), std::find(board.begin(), board.end(), 0));
        auto zero = std::make_pair(zeroIndex % size, zeroIndex / size);

        static const std::array<std::pair<int, int>, 4> moves = {
                std::make_pair(1, 0),
                std::make_pair(-1, 0),
                std::make_pair(0, -1),
                std::make_pair(0, 1)
        };

        for (const auto &move: moves) {
            size_t newX = zero.first + move.first;
            size_t newY = zero.second + move.second;

            if (newX < static_cast<size_t>(size) && newY < static_cast<size_t>(size)) {
                std::vector<int> newBoard = board;
                std::swap(newBoard[zero.second * size + zero.first], newBoard[newY * size + newX]);
                successors.emplace_back(std::make_shared<Node>(std::move(newBoard), me));
            }
        }
    }

    bool NodeComparator_AStar::operator()(const std::shared_ptr<Node> &lhs, const std::shared_ptr<Node> &rhs) const {
        return lhs->getScore() > rhs->getScore();
    }

    bool NodeComparator_Greedy::operator()(const std::shared_ptr<Node> &lhs, const std::shared_ptr<Node> &rhs) const {
        return lhs->getHeuristic() > rhs->getHeuristic();
    }

    bool
    NodeComparator_UniformCost::operator()(const std::shared_ptr<Node> &lhs, const std::shared_ptr<Node> &rhs) const {
        return lhs->getCost() > rhs->getCost();
    }
}
