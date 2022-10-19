#ifndef __BOARD_H__
#define __BOARD_H__

#define BOARD_DIM 3

#include <utility>
#include <vector>

struct Board {
    Board();
    Board(int board[BOARD_DIM][BOARD_DIM]) {
        for(int i = 0; i < BOARD_DIM; i++) {
            for(int j = 0; j < BOARD_DIM; j++) {
                if(board[i][j] == 0) {
                    zeroTile = std::make_pair(i , j);
                }
                data[i][j] = board[i][j];
            }
        }
    };
    std::pair<int, int> zeroTile;
    int data[BOARD_DIM][BOARD_DIM];
    const unsigned int n = BOARD_DIM;
};

#endif // __BOARD_H__
