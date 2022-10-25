#ifndef __PROBLEM_H__
#define __PROBLEM_H__
#include <functional>
#include <vector>
#include "board.h"
#include "node.h"

/* Defined in search.cpp */
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
    bool goalTest(Board state) {
        int count = 1;
        for(unsigned int i = 0; i < state.n; i++) {
            for(unsigned int j = 0; j < state.n; j++) {
                if(i == state.n - 1 && j == state.n - 1) count = 0;
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
