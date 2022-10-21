#ifndef __PROBLEM_H__
#define __PROBLEM_H__
#include <functional>
#include <vector>
#include "board.h"
#include "node.h"

struct Problem {
    Problem(Board state): initialState(state) {}
    Board initialState;
    std::vector<std::function<Node*(Node*)>> operators;
    bool goalTest(Board state) {
        int count = 1;
        for(int i = 0; i < state.n; i++) {
            for(int j = 0; j < state.n; j++) {
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
