 So... for this, I'm going to make a treenode class, that makes a tree. 
 PSEUDOCODE: (class TreeNode)
 
Private:
  Board * myBoard
  int bscore, wscore, and bool delete_children
  Side myside;
  vector<TreeNode *> children 

Constructor (@params Board * initial_board, side):
  myBoard = initial_board
  bscore = myboard->count(BLACK)
    // Similarly for white...
  myside = side // whos turn is it
  delete_children = true;
  
Destructor (_):
  delete myBoard
  if (delete_children is True)  {
    while (!children.empty()):
      * child = children.back();
      children.pop_back();
      delete child;
  }
  
TreeNode * getChild(int idx)	{
  return children[idx]
}

void generate_children():
  if children is not empty --> RETURN;
  ---------
  vector<Move *> moves = myboard->getPossibleMoves(myside)
  for (move in moves):
    * newboard = myboard->copy
    newboard.do_move(move)
    * child = new TreeNode(newboard, TOGGLE myside)
    children.append(child)