#ifndef __TREENODE_H__
#define __TREENODE_H__

#include "common.h"
#include "board.h"
#include <vector>

class TreeNode	{
private:
    Board * myBoard;
    int bscore, wscore;  // score variables
    int heuristic;  // is heuristic value of this branch of the tree
    bool delete_children;  // Sets whether we delete child nodes in destructor
    Side myside;  // whose turn is it???
    Side playerside; // color player is playing as
    std::vector<TreeNode *> children;

public:
    TreeNode(); // Constructs with starter board.
    TreeNode(Board * init_board, Side side, Side player); // Constructs with given board and side
    ~TreeNode(); // Destructor
    void setDeleteChildren(bool b);
    TreeNode * getChild(int idx);
    void setHeuristic(int h);
    int getHeuristic();
    int getScore(Side side);
    
    void generateChildren();  // Most important function, the node makes 
			      // children based on possible moves
    
    void minimaxCompute(int depth);
};

#endif