#include "Node.hpp"

#include <algorithm>
#include <cmath>

Node::Node(const std::vector<int> &board, const std::shared_ptr<Heuristic> &heuristic,
           const std::shared_ptr<Node> &parent) : board(board),
                                                  parent(parent),
                                                  heuristic(heuristic) {
    if (parent)
        cost = parent->getCost() + 1;
}

const std::shared_ptr<Node> &Node::getParent() const { return parent; }

const std::vector<int> &Node::getBoard() const { return board; }

std::vector<std::shared_ptr<Node>> Node::getSuccessors() const {
    int size = (int) std::sqrt(board.size());
    std::pair<int, int> zero;
    {
        auto zeroIndex = std::distance(board.begin(), std::find(board.begin(), board.end(), 0));
        zero = {zeroIndex % size, zeroIndex / size};
    }

    std::vector<std::pair<int, int>> moves = {
            {zero.first + 1, zero.second},
            {zero.first - 1, zero.second},
            {zero.first,     zero.second - 1},
            {zero.first,     zero.second + 1}};

    std::vector<std::shared_ptr<Node>> successors;
    for (const auto &move: moves) {
        if (move.first < 0 || move.first >= size || move.second < 0 || move.second >= size)
            continue;

        std::vector<int> newBoard = board;
        std::swap(newBoard[zero.second * size + zero.first], newBoard[move.second * size + move.first]);

        successors.emplace_back(std::make_shared<Node>(newBoard, heuristic, std::make_shared<Node>(*this)));
    }

    return successors;


}

int Node::getCost() const { return cost; }

int Node::getHeuristic() const { return heuristic ? heuristic->calculate(board) : 0; }

int Node::getScore() const { return getCost() + getHeuristic(); }

bool AStarComparator::operator()(const std::shared_ptr<Node> &lhs, const std::shared_ptr<Node> &rhs) const {
    return lhs->getScore() > rhs->getScore();
}

bool GreedyComparator::operator()(const std::shared_ptr<Node> &lhs, const std::shared_ptr<Node> &rhs) const {
    return lhs->getHeuristic() > rhs->getHeuristic();
}

bool UniformCostComparator::operator()(const std::shared_ptr<Node> &lhs, const std::shared_ptr<Node> &rhs) const {
    return lhs->getCost() > rhs->getCost();
}
