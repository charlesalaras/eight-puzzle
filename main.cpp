#include <iostream>
#include <sstream>
#include <string>
#include <chrono>
#include "board.h"
#include "search.h"
#include "problem.h"

extern Queue nodes;
// Activates timer & suppresses output when true
bool DEBUG = false;
// Defines the search algorithm used
enum ALGORITHM { UNIFORM, A_STAR_MT, A_STAR_MD };

// Gets input from user
char getInput() {
    char input;
    std::cout << "> ";
    std::cin >> input;
    std::cin.ignore(256, '\n');
    return input;
}

// Prompt and grab user input
void populateBoard(int board[BOARD_DIM][BOARD_DIM]) {
    unsigned int j = 0;
    while(j < (BOARD_DIM * BOARD_DIM)) {
        if(j % BOARD_DIM == 0) std::cout << "Enter row " << (j / BOARD_DIM) + 1 << ":\n";
        std::stringstream ss;
        std::string input;
        std::getline(std::cin, input);
        ss.str(input);
        std::string curr;
        while(ss >> curr) {
            board[j / BOARD_DIM][j % BOARD_DIM] = std::stoi(curr);
            j++;
        }
    }
}

int main (int argc, char* argv[]) {
    // Used to activate timer
    if(argc > 1 && std::string(argv[1]) == "-t") DEBUG = true;

    ALGORITHM search = UNIFORM;
    int boardData[BOARD_DIM][BOARD_DIM] = {
        { 1, 2, 3, },
        { 5, 0, 6, },
        { 4, 7, 8, },
    };

    std::cout << "8 Puzzle Solver - Charles Alaras 2022\n" << std::endl;
    bool inputLoop = true;
    // Until a valid option is made, choose between default configuration or a custom configuration
    while(inputLoop) {
        std::cout << "Select an initial state:\n"
                     "(0) Default Puzzle\n"
                     "(1) Custom Puzzle" << std::endl;

        char userInput = getInput();

        switch(userInput) {
            case '0':
                // Use default
                inputLoop = 0;
                break;
            case '1':
                populateBoard(boardData);
                inputLoop = 0;
                break;
            default:
                std::cout << "Error: Invalid choice.\n" << std::endl;
                continue;
        }
    }
    std::cout << std::endl;
    inputLoop = true;
    // Until a valid option is made, choose a search algorithm
    while(inputLoop) {
        std::cout << "Choose a search algorithm:\n"
                     "(0) Uniform Cost Search\n"
                     "(1) A-Star with Misplaced Tile Heuristic\n"
                     "(2) A-Star with Manhattan Heuristic" << std::endl;
        char userInput = getInput();

        switch(userInput) {
            case '0':
                search = UNIFORM;
                inputLoop = !inputLoop;
                break;
            case '1':
                search = A_STAR_MT;
                inputLoop = !inputLoop;
                break;
            case '2':
                search = A_STAR_MD;
                inputLoop = !inputLoop;
                break;
            default:
                std::cout << "Error: Invalid choice.\n" << std::endl;
                continue;
        }
    }
    // Problem initialization with created state and chosen algorithm
    Board board(boardData);
    Problem problem(board);
    Node* solution = nullptr;
    std::function<Queue(Queue&, std::vector<Node*>)> queueingFunction;
    switch(search) {
        case UNIFORM:
            queueingFunction = &uniformCost;
            break;
        case A_STAR_MT:
            queueingFunction = &misplacedTile;
            break;
        case A_STAR_MD:
            queueingFunction = &manhattanDist;
            break;
    }
    // Timer starts here (if flag "-t" is passed)
    std::chrono::steady_clock::time_point t1;
    if(DEBUG) t1 = std::chrono::steady_clock::now();

    solution = generalSearch(problem, queueingFunction);

    // Timer ends here and prints out duration (if flag "-t" is passed)
    if(DEBUG) {
        auto t2 = std::chrono::steady_clock::now();
        std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
        std::cout << "Runtime duration: " << time_span.count() << std::endl;
    }
    if(solution != nullptr) {
        std::cout << "Goal state!\n" << std::endl;
        std::cout << "Solution depth was " << solution->pathCost << std::endl;
        std::cout << "Number of nodes expanded: " << nodes.expanded << std::endl;
        std::cout << "Max queue size: " << nodes.maxSize << std::endl;
        delete solution;
    }
    // Do final cleanup of queue and nodes
    nodes.clear();
    return 0;
} 
