#ifndef __PROBLEM_H__
#define __PROBLEM_H__
#include <functional>
#include <vector>
#include "board.h"
#include "node.h"

/* Operators defined in search.cpp */
Node* slideLeft(Node*);
Node* slideRight(Node*);
Node* slideUp(Node*);
Node* slideDown(Node*);

struct Problem {
    Problem(Board state): initialState(state) {}
    Board initialState;
    std::vector<std::function<Node*(Node*)>> operators = {
        slideLeft,
        slideRight,
        slideUp,
        slideDown
    };
    // Tests a given board to see if its the goal
    bool goalTest(Board state) {
        int count = 1;
        for(unsigned int i = 0; i < BOARD_DIM; i++) {
            for(unsigned int j = 0; j < BOARD_DIM; j++) {
                if(i == BOARD_DIM - 1 && j == BOARD_DIM - 1) count = 0;
                if(state.data[i][j] != count) {
                    return false;
                }
                count = count + 1;
            }
        }
        return true;
    }
};

#endif // __PROBLEM_H__
