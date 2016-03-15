#include "player.h"
#include <vector>
#define MAX(a, b) (((a) > (b)) ? (a) : (b)) 

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish 
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    /* 
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
    myBoard = new Board();
    mySide = side;
     if (mySide == BLACK)	{
       other = WHITE;
       movenum = 0; // we start at move #1
     }
     else	{
       other = BLACK;
       movenum = 1;
     }
    //myTree = new TreeNode(myBoard, BLACK, mySide);
}

/*
 * Destructor for the player.
 */
Player::~Player() {
  delete myBoard;
  delete bestmove;
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be NULL.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return NULL.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /* 
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */ 
    movenum++;
    myBoard->doMove(opponentsMove, other);
    
    std::vector<Move *> moves = myBoard->getPossibleMoves(mySide);
    //std::cerr << "got possible moves";
    if (moves.size() == 0) { return NULL; }
    if (testingMinimax)   {
       int b = minimax(myBoard, 2, 0, 1);
       myBoard->doMove(bestmove, mySide);
       return bestmove;
    }
    
    int idx = 0;
    int score = 0;
    for (int i = 0; i < moves.size(); i++)	{
      int x = moves[i]->getX();
      int y = moves[i]->getY();
      if ((x == 0 || x == 7)&&(y == 0 || y == 7))	{
	bestmove = moves[i]; // yay corner!
	myBoard->doMove(bestmove, mySide);
	return bestmove;
      }
      else if (((x == 0 || x == 7) && (y != 1 && y != 6)) || ((y == 0 || y == 7) && (x != 1 && x != 6)))	{
	idx = i;
	score = 20; // some kinda guess as to how better an edge is compared with mobility
      }
    }
    int b = negamax(myBoard, 6, 0, 1, -1000, 1000);
    if (score > b)	{
      bestmove = moves[idx];
    }
    
    //std::cerr << "bestmove is now (" << bestmove->getX() << ", " << bestmove->getY() << ")  \n";
    myBoard->doMove(bestmove, mySide);
    //std::cerr << "Did move.\n";
    return bestmove;
}

Move *Player::greedy(Move *opponentsMove) {
    // is a greedy (look down one move) heuristic
    // for playing, and prioritizes corners.
    
    std::vector<Move *> moves = myBoard->getPossibleMoves(mySide);
    if (moves.size() == 0)	{
      return NULL;
    }
    int idx = 0;
    int hdx = -1000;
    Board * copyboard;
    for (int i = 0; i < moves.size(); i++)	{
      copyboard = myBoard->copy();
      copyboard->doMove(moves[i], mySide);
      int x = moves[i]->getX();
      int y = moves[i]->getY(); 
      if ((x == 0 || x == 7)&&(y == 0 || y == 7))	{
	myBoard->doMove(moves[i], mySide);
	return moves[i];
      }
      else if (((x == 0 || x == 7) && (y != 1 && y != 6)) || ((y == 0 || y == 7) && (x != 1 && x != 6)))	{
	myBoard->doMove(moves[i], mySide);
	return moves[i];
      }
      int c = copyboard->count(mySide) - copyboard->count(other);
      if ((x == 1 && y == 1) || (x == 6 && y == 1) || (x == 1 && y == 6) || (x == 6 && y == 6))	{
	c = c - 20;
      }
      if (hdx < c)	{
	hdx = c;
	idx = i;
      }
      delete copyboard;
    }
    myBoard->doMove(moves[idx], mySide);
    return moves[idx];
}

int Player::minimax(Board * board, int depth, int depthAt, int color)   {
     std::cerr << "Reached minimax call\n";
     std::cerr << "board is at  " << board << "\n"; 
     if (depth == depthAt)	{ // base case - end of search
        std::cerr << "entered if statement - board is at  " << board << "\n"; 
        return color*(board->count(mySide) - board->count(other));
     }
     std::cerr << "About to get possible moves\n";
     std::vector<Move *> moves = board->getPossibleMoves((color == 1)?mySide:other);
     std::cerr << "Got possible moves\n";
     if (moves.size() == 0)	{
       std::cerr << "Moves size is zero here\n";
       return color*(board->count(mySide) - board->count(other));
     }
     std::cerr << "made moves vector\n";
     int bestvalue = -1000;
     int v;
     int idx = 0;
     Board * copyboard;
     for (int i = 0; i < moves.size(); i++)	{
       copyboard = board->copy();
       copyboard->doMove(moves[i], (color == 1)?mySide:other);
       v = -1*minimax(copyboard, depth, depthAt+1, -1*color);
       if (v > bestvalue)	{
	 bestvalue = v;
	 idx = i;
       }
       delete copyboard;  // clean up memory
     }
     
     std::cerr << "About to create bye\n";
     Move * bye = bestmove;
     std::cerr << "created bye\n";
     std::cerr << "Moves size is " << moves.size() << "\n";
     std::cerr << "moves idx is " << idx;
     std::cerr << " and move is (" << moves[idx]->getX() << ", " << moves[idx]->getY() << ")  \n";
     bestmove = new Move(moves[idx]->getX(), moves[idx]->getY());
     if (bye != NULL)  {
       delete bye;
       std::cerr << "deleted bye\n";
     }
     std::cerr << "Reached end of minimax call\n";
     return bestvalue;
}

int Player::negamax(Board * board, int depth, int depthAt, int color, int alpha, int beta)   {
     if (depth == depthAt)	{ // base case - end of search
        return getHeuristic(board, color);
     }
     std::vector<Move *> moves = board->getPossibleMoves((color == 1)?mySide:other);
     if (moves.size() == 0)	{
       return getHeuristic(board, color);
     }
     int bestvalue = -1000;
     int v;
     int idx = 0;
     Board * copyboard;
     for (int i = 0; i < moves.size(); i++)	{
       copyboard = board->copy();
       copyboard->doMove(moves[i], (color == 1)?mySide:other);
       v = -1*negamax(copyboard, depth, depthAt+1, -1*color, -1*beta, -1*alpha);
       if (v > bestvalue)	{
	 bestvalue = v;
	 idx = i;
       }
       alpha = MAX(alpha, v);
       if (alpha >= beta)   {
	 delete copyboard;
	 break;
       }
       delete copyboard;  // clean up memory
     }
     
     Move * bye = bestmove;
     bestmove = new Move(moves[idx]->getX(), moves[idx]->getY());
     if (bye != NULL)  {
       delete bye;
     }
     return bestvalue;
}

int Player::getHeuristic(Board * board, int color)	{
  Side them = (color == -1)?mySide:other;
  Side us = (color == 1)?mySide:other;
  std::vector<Move *> moves = board->getPossibleMoves(us);
  int idx = 0;
  int mobility = moves.size();
  mobility = (int) (mobility * 6.4); // converts from "number of moves" scale to 
      // "points" scale, as there are an average of 10 moves available, and 64 squares
  
  if (moves.size() <= 2)  {
    mobility = color*(board->count(us) - board->count(them));
  }
  else   {
    // Do nothing
  }
  /*for (int i = 0; i < moves.size(); i++)	{
      int x = moves[i]->getX();
      int y = moves[i]->getY();
      if ((x == 0 || x == 7)&&(y == 0 || y == 7))	{
	return color*100; // corner!
      }
      else if (((x == 0 || x == 7) && (y != 1 && y != 6)) || ((y == 0 || y == 7) && (x != 1 && x != 6)))	{
	return color*50; // get non corner adjacent edges?
      }
  }*/
  return color*mobility;
}