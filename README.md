Caltech CS2 Assignment 9: Othello

See [assignment9_part1.html](http://htmlpreview.github.io/?https://github.com/caltechcs2/othello/blob/master/assignment9_part1.html) and [assignment9_part2.html](http://htmlpreview.github.io/?https://github.com/caltechcs2/othello/blob/master/assignment9_part2.html)

PART II written thing:
------------------------
I was solo for this. 

This will be my submission for the tournament. This thing will first:
   - Prioritize corners; if there is a corner, we TAKE IT.
   - Looks if we have a non corner adjacent edge move, and save it.
   - Do minimax depth 6 using a mobility heuristic, unless it has 2
     or fewer moves left, where it switches to greedy heuristic
   
Now, it looks at the score of 20 (this is just a guess) we have if we have an edge move,
and