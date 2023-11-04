#include "Search.hpp"

#include <iostream>
#include <chrono>
#include <fstream>
#include <functional>

using namespace NPuzzle;

Puzzle createPuzzle(int argc, char **argv) {
    if (argc == 2) {
        std::string arg1(argv[1]);
        if (arg1.find(".txt") != std::string::npos)
            return Puzzle(arg1);
        else if (arg1.find_first_not_of("0123456789") == std::string::npos)
            return Puzzle(std::stoi(arg1));
        else
            throw std::invalid_argument("Invalid argument. Provide a .txt file or a numeric puzzle size.");
    } else
        return Puzzle();
}

template<typename T>
T getUserChoice(const std::string &message, const std::vector<std::string> &choices) {
    for (size_t i = 0; i < choices.size(); ++i)
        std::cout << (i + 1) << ". " << choices[i] << std::endl;

    size_t choice = -1;
    do {
        std::cout << message;
        if (!(std::cin >> choice) || choice < 1 || choice > choices.size()) {
            std::cout << "Invalid choice. Please enter a number between 1 and " << choices.size() << "." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else
            break;
    } while (true);

    return T(choice - 1);
}

std::shared_ptr<Heuristic> createHeuristic(int index) {
    static const std::array<std::shared_ptr<Heuristic>, 3> heuristics = {
            std::make_shared<Heuristic_MisplacedTiles>(),
            std::make_shared<Heuristic_ManhattanDistance>(),
            std::make_shared<Heuristic_LinearConflict>()
    };
    return heuristics[index];
}

std::unique_ptr<SearchBase> createAlgorithm(int index) {
    static const std::array<std::function<std::unique_ptr<SearchBase>()>, 3> algorithms = {
            []() { return std::make_unique<Search<NodeComparator_AStar>>(); },
            []() { return std::make_unique<Search<NodeComparator_Greedy>>(); },
            []() { return std::make_unique<Search<NodeComparator_UniformCost>>(); }
    };
    return algorithms[index]();
}

void solve(Puzzle &puzzle) {
    std::cout << "Initial puzzle state:\n" << puzzle << std::endl;

    auto heuristic = createHeuristic(getUserChoice<int>(
            "Choose a heuristic: ",
            {"Misplaced tiles", "Manhattan distance", "Linear conflict"}
    ));

    auto algorithm = createAlgorithm(getUserChoice<int>(
            "Choose an algorithm: ",
            {"A*", "Greedy", "Uniform cost"}
    ));

    auto start = std::chrono::steady_clock::now();
    auto path = algorithm->solve(puzzle, heuristic);
    auto end = std::chrono::steady_clock::now();

    if (!path) {
        std::cout << "No solution found." << std::endl;
        return;
    }

    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Solution found in " << elapsed_seconds.count() << " seconds, "
              << "with " << path->size() - 1 << " moves." << std::endl;
    algorithm->printStats();

    std::ofstream solutionFile("solution.txt");
    if (!solutionFile.is_open())
        throw std::runtime_error("Failed to open file to write solution.");
    while (!path->empty()) {
        solutionFile << path->top() << "\n\n";
        path->pop();
    }
}

int main(int argc, char **argv) {
    try {
        Puzzle puzzle = createPuzzle(argc, argv);
        solve(puzzle);
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
