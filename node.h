#ifndef __NODE_H__
#define __NODE_H__

#include "board.h"

struct Node {
    Node() = default;
    Node(Board state): state(state) {}
    Node(int pc, int h): pathCost(pc), heuristic(h) {}
    Board state;
    int pathCost = 0;
    int heuristic = 0;
};

#endif // __NODE_H__
