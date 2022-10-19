#ifndef __PROBLEM_H__
#define __PROBLEM_H__
#include <functional>
#include <vector>
#include "board.h"
#include "node.h"

class Problem {
    public:
        Board initialState;
        bool goalTest(Board state);
        std::vector<std::function<Node*(Board)>> operators;
};

#endif // __PROBLEM_H__
