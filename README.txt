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

    
------------------------------------------------------------

Now, we will implement the pseudocode for the minimax. Wikipedia's pseudocode
looks like this...
01 function minimax(node, depth, maximizingPlayer)
02     if depth = 0 or node is a terminal node
03         return the heuristic value of node

04     if maximizingPlayer
05         bestValue := −∞
06         for each child of node
07             v := minimax(child, depth − 1, FALSE)
08             bestValue := max(bestValue, v)
09         return bestValue

10     else    (* minimizing player *)
11         bestValue := +∞
12         for each child of node
13             v := minimax(child, depth − 1, TRUE)
14             bestValue := min(bestValue, v)
15         return bestValue
(Yeah, that's wikipedia.)

We are the maximizing player. So instead, we know we are the maximizing 
player if the myside in the TreeNode equals the Playerside. Otherwise,
we know we are the minimizing player.

Also, instead of returning bestvalue, we will instead assign it to 
the heuristic.
However, our heuristic will now check for corners. Thus, before we go
into the recursive calls of the children, we will first check whether
making a move will "give" our opponent a corner. If we do, we alter 
the heuristic to be a big negative value, say, -100. Otherwise, we
use the simple counting heuristic.

-- PSEUDOCODE --
@ Precondition: initial depth is even.
void minimaxCompute(depth)	{
  if (depth = 0):
    if (we can get a corner)
      heuristic = +100, return;
    else, heuristic = count(us) - count(them), then return;
  
  vector<Move *> moves = myBoard->getPossibleMoves();
  if (moves is empty)   { //it's terminal
    if (we win)
      heuristic = +1000
    else if (they win)
      heuristic = -1000;
    else
      heuristic = 0
    return;
  }
  
  if (playerside == myside)   { // is maximizing player
    arr[] hs = int arr[children.size]
    for (i = 0 thru children.size())	{
      children[i]->minimax(depth-1);
      hs[i] = children[i]->getHeuristic()
    }
    heuristic = MAX(hs);
  }
  
  elseif (playerside != myside)   { // is minimizing player
    arr[] hs = int arr[children.size]
    for (i = 0 thru children.size())	{
      children[i]->minimax(depth-1);
      hs[i] = children[i]->getHeuristic()
    }
    heuristic = MIN(hs);
  }
}