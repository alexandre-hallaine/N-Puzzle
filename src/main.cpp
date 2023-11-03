#include "Search.hpp"

#include <iostream>
#include <chrono>
#include <fstream>
#include <utility>

void error(const std::string &message, int code = 1) {
    std::cerr << message << std::endl;
    exit(code);
}

int input(const std::string &message, int length) {
    std::string input;
    int choice;

    do {
        std::cout << message;
        std::getline(std::cin, input);

        try {
            choice = std::stoi(input);
            if (choice < 1 || choice > length)
                std::cout << "That's not a valid choice" << std::endl;
            else
                break;
        }
        catch (std::exception &e) {
            std::cout << "That's not a number" << std::endl;
        }
    } while (true);
    std::cout << std::endl;
    return choice;
}

Puzzle getPuzzle(int argc, char **argv) {
    if (argc > 2)
        error("Usage: " + std::string(argv[0]) + " [filename/size]", 2);

    std::unique_ptr<Puzzle> puzzle;
    try {
        if (argc != 2)
            puzzle = std::make_unique<Puzzle>();
        else if (std::string(argv[1]).find(".txt") != std::string::npos)
            puzzle = std::make_unique<Puzzle>(std::string(argv[1]));
        else if (std::string(argv[1]).find_first_not_of("0123456789") == std::string::npos)
            puzzle = std::make_unique<Puzzle>(std::stoi(argv[1]));
        else
            error("Invalid argument", 2);
    }
    catch (std::exception &e) {
        error(e.what(), 2);
    }

    std::cout << "Initial puzzle:" << std::endl
              << *puzzle << std::endl
              << std::endl;
    return *puzzle;
}

std::shared_ptr<Heuristic> getHeuristic() {
    std::cout << "Available heuristics:" << std::endl;
    std::array<std::shared_ptr<Heuristic>, 3> heuristics = {
            std::make_shared<MisplacedTiles>(),
            std::make_shared<ManhattanDistance>(),
            std::make_shared<LinearConflict>()};

    int i = 0;
    for (std::string heuristic: {"Misplaced tiles", "Manhattan distance", "Linear conflict"})
        std::cout << ++i << ". " << heuristic << std::endl;
    std::cout << std::endl;

    int choice = input("Choose a heuristic: ", heuristics.size());
    return std::move(heuristics[choice - 1]);
}

std::unique_ptr<SearchBase> getAlgorithm(const std::shared_ptr<Heuristic> &heuristic) {
    std::cout << "Available algorithms:" << std::endl;
    std::array<std::unique_ptr<SearchBase>, 3> algorithms = {
            std::make_unique<Search<AStarComparator>>(heuristic),
            std::make_unique<Search<GreedyComparator>>(heuristic),
            std::make_unique<Search<UniformCostComparator>>(heuristic)};

    int i = 0;
    for (std::string algorithm: {"A*", "Greedy", "Uniform cost"})
        std::cout << ++i << ". " << algorithm << std::endl;
    std::cout << std::endl;

    int choice = input("Choose an algorithm: ", algorithms.size());
    return std::move(algorithms[choice - 1]);
}

void solve(std::unique_ptr<SearchBase> search, const Puzzle &puzzle) {
    auto start = std::chrono::steady_clock::now();
    std::unique_ptr<std::stack<Puzzle>> path = search->solve(puzzle);
    auto end = std::chrono::steady_clock::now();

    if (path == nullptr) {
        std::cout << "No solution found" << std::endl;
        return;
    }

    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Elapsed time: " << elapsed_seconds.count() << "s" << std::endl;
    std::cout << "Solution found in " << path->size() - 1 << " moves" << std::endl;
    search->printStats();

    std::ofstream solution("solution.txt");
    if (!solution.is_open())
        error("Could not open solution.txt", 4);
    while (!path->empty()) {
        solution << path->top() << std::endl
                 << std::endl;
        path->pop();
    }
}

int main(int argc, char **argv) {
    Puzzle puzzle = getPuzzle(argc, argv);
    solve(getAlgorithm(getHeuristic()), puzzle);
}
