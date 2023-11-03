#include "Node.hpp"

#include <algorithm>
#include <cmath>

Node::Node(const std::vector<int> &board, int size, const std::shared_ptr<Heuristic> &heuristic,
           const std::shared_ptr<Node> &parent) : board(board),
                                                  parent(parent),
                                                  heuristic(heuristic),
                                                  size(size) {
    if (parent)
        cost_value = parent->getCost() + 1;
    if (heuristic == nullptr)
        throw std::invalid_argument("Heuristic cannot be null");
    heuristic_value = heuristic->calculate(board, size);
}

Node::Node(const Puzzle &puzzle, const std::shared_ptr<Heuristic> &heuristic) : Node(puzzle.getBoard(),
                                                                                     puzzle.size, heuristic,
                                                                                     nullptr) {}

const std::shared_ptr<Node> &Node::getParent() const { return parent; }

const std::vector<int> &Node::getBoard() const { return board; }

std::vector<std::shared_ptr<Node>> Node::getSuccessors() const {
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

        Node successor(newBoard, size, heuristic, std::make_shared<Node>(*this));
        successors.emplace_back(std::make_shared<Node>(successor));
    }

    return successors;


}

int Node::getCost() const { return cost_value; }

int Node::getHeuristic() const { return heuristic_value; }

int Node::getScore() const { return cost_value + heuristic_value; }

bool AStarComparator::operator()(const std::shared_ptr<Node> &lhs, const std::shared_ptr<Node> &rhs) const {
    return lhs->getScore() > rhs->getScore();
}

bool GreedyComparator::operator()(const std::shared_ptr<Node> &lhs, const std::shared_ptr<Node> &rhs) const {
    return lhs->getHeuristic() > rhs->getHeuristic();
}

bool UniformCostComparator::operator()(const std::shared_ptr<Node> &lhs, const std::shared_ptr<Node> &rhs) const {
    return lhs->getCost() > rhs->getCost();
}

Puzzle Node::getPuzzle() const { return Puzzle(board); }
