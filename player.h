#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.h"
#include "board.h"
#include "TreeNode.h"
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();
    
    Move *doMove(Move *opponentsMove, int msLeft);
    Move *greedy(Move *opponentsMove);
    int minimax(Board * board, int depth, int depthAt, int color);
    Board * myBoard;
    // TreeNode * myTree;
    Side mySide;
    Side other;
    Move * bestmove;

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
};

#endif
