/* Total number of spanning trees in a complete graph
with n vertices is given by n^(n-2) */

/* Sprague-Grundy Theorem: The losing states are exactly 
those with Grundy number equal to 0.
Grundy number of the current state is the smallest whole 
number which is not the Grundy number of any state that 
can be reached in the next step. 
Mathematically, if s1, s2 … sk are the game states directly 
reachable from s, 
Grundy(s)=min({0,1,...} - {Grundy(s1),Grundy(s2)…Grundy(sk)}) */

/* Sums of Games:
1. Player chooses a game and makes a move in it. Grundy number 
of a position is xor of grundy numbers of positions in summed games. 
2. Player chooses a non-empty subset of games (possibly, all) and 
makes moves in all of them. A position is losing iff each game 
is in a losing position.
3.Player chooses a proper subset of games (not empty and not all), 
and makes moves in all chosen ones. A position is losing iff grundy 
numbers of all games are equal.
4. Player must move in all games, and loses if can’t move in some game.
A position is losing if any of the games is in a losing position. */

/* Misere Nim. A position with pile sizes a1, a2,..., an >= 1, not all 
equal to 1, is losing iff a1 xor a2 ... xor an = 0 (like in normal nim.) 
A position with n piles of size 1 is losing iff n is odd. */