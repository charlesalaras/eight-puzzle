#include <iostream>
#include <sstream>
#include "board.h"
#include "search.h"
#include "problem.h"

// Defines the search algorithm used
enum ALGORITHM { UNIFORM, A_STAR_MT, A_STAR_MD };

// Gets input from user
std::string getInput() {
    std::string input;
    std::cout << "> ";
    std::cin >> input;
    return input;
}

void populateBoard(Board board) {
    for(unsigned int i = 0; i < BOARD_DIM; i++) {
        std::cout << "Enter row " << i + 1 << ":";
        unsigned int j = 0;
        std::stringstream ss;
        
    }
}

int main () {

    ALGORITHM search = UNIFORM;
    int boardData[BOARD_DIM][BOARD_DIM] = {
        { 1, 2, 3, },
        { 5, 0, 6, },
        { 4, 7, 8, },
    };

    std::cout << "8 Puzzle Solver - Charles Alaras 2022\n" << std::endl;
    bool inputLoop = true;
    while(inputLoop) {
        std::cout << "Select an initial state:\n"
                     "(0) Default Puzzle\n"
                     "(1) Custom Puzzle" << std::endl;

        int userInput = std::stoi(getInput());

        switch(userInput) {
            case 0:
                // Use default
                inputLoop = 0;
                break;
            case 1:
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
    while(inputLoop) {
        std::cout << "Choose a search algorithm:\n"
                     "(0) Uniform Cost Search\n"
                     "(1) A-Star with Misplaced Tile Heuristic\n"
                     "(2) A-Star with Manhattan Heuristic" << std::endl;
        int userInput = std::stoi(getInput());

        switch(userInput) {
            case 0:
                search = UNIFORM;
                inputLoop = !inputLoop;
                break;
            case 1:
                search = A_STAR_MT;
                inputLoop = !inputLoop;
                break;
            case 2:
                search = A_STAR_MD;
                inputLoop = !inputLoop;
                break;
            default:
                std::cout << "Error: Invalid choice.\n" << std::endl;
                continue;
        }
    }
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
    solution = generalSearch(problem, queueingFunction);
    return 0;
} 
