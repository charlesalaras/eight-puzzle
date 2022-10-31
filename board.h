#ifndef __BOARD_H__
#define __BOARD_H__

#define BOARD_DIM 3

#include <iostream>
#include <utility>
#include <vector>

struct Board {
    std::pair<unsigned int, unsigned int> zeroTile;
    int data[BOARD_DIM][BOARD_DIM] = { 0 };
    Board() {
        int seen[BOARD_DIM] = { 0 };
        for(unsigned int i = 0; i < BOARD_DIM; i++) {
            for(unsigned int j = 0; j < BOARD_DIM; j++) {
                int insert = rand() % BOARD_DIM;
                while(seen[insert] == 1) insert = rand() % BOARD_DIM;
                if(insert == 0) zeroTile = {i , j};
                data[i][j] = rand() % BOARD_DIM;
                seen[insert]++;
            }
        }
    }
    Board(int board[BOARD_DIM][BOARD_DIM]) {
        for(int i = 0; i < BOARD_DIM; i++) {
            for(int j = 0; j < BOARD_DIM; j++) {
                if(board[i][j] == 0) {
                    zeroTile = { i, j };
                }
                data[i][j] = board[i][j];
            }
        }
    };
    void print() {
        std::string output = "";
        for(int i = 0; i < BOARD_DIM; i++) {
            output += "[ ";
            for(int j = 0; j < BOARD_DIM; j++) {
                output += std::to_string(data[i][j]) + " ";
            }
            output += "]\n";
        }
        std::cout << output;
    }
    std::string stringify() {
        std::string output = "";
        for(int i = 0; i < BOARD_DIM; i++) {
            for(int j = 0; j < BOARD_DIM; j++) {
                output += std::to_string(data[i][j]);
            }
        }
        return output;
    }
};

#endif // __BOARD_H__
