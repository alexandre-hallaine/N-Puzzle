# N-Puzzle Solver

## Overview

The N-Puzzle Solver is a versatile C++ application designed to solve N x N sliding tile puzzles. It provides an array of heuristic methods and search algorithms, allowing users to tailor the solver's strategy. Puzzles can be loaded from files or generated randomly by the program itself.

## Features

- Automatic puzzle generation for quick testing.
- User choice of heuristic methods and search algorithms.
- Supports puzzles of varying dimensions (N x N).
- Real-time performance metrics and solution statistics.
- Pre-checks for puzzle solvability.

## Prerequisites

- C++17 or higher
- Make

## Getting Started

1. **Clone the Repository**

    ```bash
    git clone https://github.com/username/N-Puzzle.git
    ```

2. **Navigate to the Directory**

    ```bash
    cd N-Puzzle
    ```

3. **Compile the Program**

    ```bash
    make
    ```

4. **Run the Program**

    ```bash
    ./n-puzzle
    ```

    Or to load a specific puzzle:

    ```bash
    ./n-puzzle example/puzzle3.txt
    ```

## Usage

### Automatic Puzzle Generation

Just run the program without any arguments to generate a random puzzle.

### File-Based Puzzles

Puzzles can be loaded from text files. The first line specifies the puzzle's dimension `N`, followed by `N * N` integers forming the puzzle board.

Example:

```
3
1 2 3
4 5 6
7 8 0
```

### Choosing Heuristics and Algorithms

Upon running, the program will prompt you to choose from available heuristics and algorithms.

## Customization

Advanced users can add their own heuristic methods and search algorithms by extending the relevant classes.

## Performance Metrics

- Elapsed time
- Solution moves
- Complexity in time
- Complexity in size

## License

This project is open-source and free to use, modify, or distribute for any purpose. However, it was developed primarily for educational purposes at 42 Paris School and is not considered production-ready. Use at your own risk.
