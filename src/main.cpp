#include "Search.hpp"

#include <iostream>
#include <chrono>
#include <fstream>
#include <utility>

void error(const std::string &message, int code = 1) {
    std::cerr << message << std::endl;
    exit(code);
}

unsigned char input(const std::string &message, unsigned char length) {
    std::string input;
    unsigned char choice;

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
        error("Usage: " + std::string(argv[0]) + " [filename]", 1);

    std::unique_ptr<Puzzle> puzzle;
    try {
        if (argc == 2)
            puzzle = std::make_unique<Puzzle>(std::string(argv[1]));
        else
            puzzle = std::make_unique<Puzzle>();
    }
    catch (std::exception &e) {
        error(e.what(), 2);
    }

    std::cout << "Initial puzzle:" << std::endl
              << *puzzle << std::endl
              << std::endl;
    return *puzzle;
}

std::unique_ptr<Heuristic> getHeuristic() {
    std::array<std::unique_ptr<Heuristic>, 3> heuristics = {
            std::make_unique<MisplacedTiles>(),
            std::make_unique<ManhattanDistance>(),
            std::make_unique<LinearConflict>()};

    std::cout << "Available heuristics:" << std::endl;
    for (auto i = 0; i < heuristics.size(); i++)
        std::cout << i + 1 << ". " << heuristics[i]->getName() << std::endl;
    std::cout << std::endl;

    unsigned char choice = input("Choose a heuristic: ", heuristics.size());
    return std::move(heuristics[choice - 1]);
}

std::unique_ptr<SearchBase> getAlgorithm(std::unique_ptr<Heuristic> heuristic) {
    std::cout << "Available algorithms:" << std::endl;

    unsigned char i = 0;
    for (std::string algorithm: {"A*", "Greedy", "Uniform cost"})
        std::cout << (int) ++i << ". " << algorithm << std::endl;
    std::cout << std::endl;

    unsigned char choice = input("Choose an algorithm: ", i);
    switch (choice) {
        case 1:
            return std::make_unique<Search<AStarComparator>>(std::move(heuristic));
        case 2:
            return std::make_unique<Search<GreedyComparator>>(std::move(heuristic));
        case 3:
            return std::make_unique<Search<UniformCostComparator>>(std::move(heuristic));
        default:
            error("Invalid algorithm choice", 3); // Should never happen
    }
    return nullptr; // Avoid warning
}

void solve(std::unique_ptr<SearchBase> search, Puzzle puzzle) {
    auto start = std::chrono::steady_clock::now();
    std::unique_ptr<std::stack<Puzzle>> path = search->solve(std::move(puzzle));
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
    std::unique_ptr<SearchBase> search = getAlgorithm(getHeuristic());
    solve(std::move(search), puzzle);
}
