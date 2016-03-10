/*
* File TreeNode.cpp
*/

#include "TreeNode.h"
#include <algorithm>
#include <iostream>

// Constructors and Destructors

TreeNode:: TreeNode(Board * init_board, Side side, Side player)	{
  myBoard = init_board;
  bscore = myBoard->countBlack();
  wscore = myBoard->countWhite();
  myside = side;
  heuristic = 0;
  delete_children = true;
  playerside = player;
}

TreeNode::TreeNode()  {
  myBoard = new Board(); // standard board
  bscore = 2;
  wscore = 2;
  myside = BLACK;
  heuristic = 0;
  delete_children = true;
  playerside = BLACK;
}

TreeNode::~TreeNode()	{
  delete myBoard;
  if (delete_children)	{
    while (!children.empty())	{
      TreeNode * child = children.back();
      children.pop_back();
      delete child;
    }
  }
}

//////////////////////////////////////////////

// Simpler functions...

TreeNode * TreeNode::getChild(int idx)	{
  return children[idx];
}

void TreeNode::setDeleteChildren(bool b)	{
  delete_children = b;
}

void TreeNode::setHeuristic(int h)	{
  heuristic = h;
}

int TreeNode::getScore(Side side)	{
  if (side == BLACK)	{
    return bscore;
  }
  else  {
    return wscore;
  }
}

int TreeNode::getHeuristic()	{
  return heuristic;
}

/////////////////////////////////////////////

void TreeNode::generateChildren()	{
  if (!(children.empty()))	return;
  // if the thing is empty, we just exit. this saves us
  // recomputation time.
  Side other;
  if (myside == BLACK)	{
    other = WHITE;
  }
  else	{
    other = BLACK;
  }
  std::vector<Move *> moves = myBoard->getPossibleMoves(myside);
  for (int i = 0; i < moves.size(); i++)	{
    Board * newBoard = myBoard->copy();
    newBoard->doMove(moves[i], myside);
    TreeNode * child = new TreeNode(newBoard, other, playerside);
    children.push_back(child);
  }
}

///////////////////////////////////////////////

/* Here we have our minimax function. See the  README.txt
 * for explanation on why it works.
 * @Precondition: depth is even.
 */
void TreeNode::minimaxCompute(int depth)	{
  Side us = playerside;
  Side them;
  if (us == BLACK)	{
    them = WHITE;
  }
  else	{
    them = BLACK;
  }
  int i;
  std::vector<Move *> moves = myBoard->getPossibleMoves(myside);
  // Base case. We handle depth = 0 (end of minimax) and an
  // actual terminal node differently...
  std::cerr << "moves size is  " << moves.size() << "\n";
  if (depth == 0 && moves.size()!= 0)	{ // base case
      for (i = 0; i < moves.size(); i++)	{
	// check if we can get a corner
	/*int x = moves[i]->getX();
	int y = moves[i]->getY(); 
	if ((x == 0 || x == 7)&&(y == 0 || y == 7))	{
	  setHeuristic(100);
	  return;
	}
	else  {*/
	  setHeuristic(myBoard->count(us) - myBoard->count(them));
	//}
      }
  }
  else if (moves.size() == 0)	{ // base case
    std::cerr << "reached ";
    int w = myBoard->count(us) - myBoard->count(them);
    if (w > 0)	{
      setHeuristic(1000);
      return;
    }
    else if (w < 0)	{
      setHeuristic(-1000);
      return;
    }
    else {
      setHeuristic(0);
      return;
    }
  }
  
  //////////////////////////////////
  generateChildren();
  if (us == myside)   { // is maximizing player
    int hs[children.size()];
    for (i = 0; i < children.size(); i++)	{
      children[i]->minimaxCompute(depth-1);
      hs[i] = children[i]->getHeuristic();
    }
    heuristic = *std::max_element(hs,hs+children.size());
  }
  
  else if (us != myside)   { // is minimizing player
    int hs[children.size()];
    for (i = 0; i < children.size(); i++)	{
      children[i]->minimaxCompute(depth-1);
      hs[i] = children[i]->getHeuristic();
    }
    heuristic = *std::min_element(hs,hs+children.size());
  }
}