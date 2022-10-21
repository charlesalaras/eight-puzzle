#ifndef __NODE_H__
#define __NODE_H__

#include "board.h"

struct Node {
    Node();
    Node(Board state): state(state) {}
    Node(int pc, int h);
    Board state;
    int pathCost;
    int heuristic = 0;
};

#endif // __NODE_H__
