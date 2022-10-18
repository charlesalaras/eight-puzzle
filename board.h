#ifndef __BOARD_H__
#define __BOARD_H__

#define BOARD_DIM 3

#include <utility>

struct Board {
    Board();
    std::pair<int, int> zeroTile;
    int data[BOARD_DIM][BOARD_DIM];
    const unsigned int n = BOARD_DIM;
};

#endif // __BOARD_H__
