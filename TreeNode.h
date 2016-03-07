#ifndef __TREENODE_H__
#define __TREENODE_H__

#include "common.h"
#include "board.h"

class TreeNode	{
private:
    Board * myBoard;
    int bscore, wscore;  // score variables
    bool delete_children;  // Sets whether we delete child nodes in destructor
    Side myside;  // whose turn is it???
    std::vector<TreeNode *> children 

public:
    TreeNode(); // Constructs with starter board.
    TreeNode(Board * init_board, Side side); // Constructs with given board and side
    ~TreeNode(); // Destructor
    void setDeleteChildren(bool b);
    TreeNode * getChild(int idx);
    
    void generate_children();  // Most important function, the node makes 
			       // children based on possible moves
}

#endif