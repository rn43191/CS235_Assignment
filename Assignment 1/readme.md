## Eight Queen Problem using UCS

- Initial State:
No queens are on the board
- States:
A state is any arrangement of 0 to 8 queens on the board. We can even have a state where any arrangement of 0-8 queens is done with no queen under attack.
- Actions:
The operators add queens to any empty square or add queen to leftmost empty square such that it is not attacked by other queens.
- Path cost:
1 per every move
- Goal state:
Arranging 8 queens on the board such that no one is under attack by any other queen.

>Uniform Cost search is basically Breadth first search if the path cost is same for every move.
---
### Compilation

```
g++ 1801140.cpp
./a.out
```
---
## I/O Files

*NO INPUT REQUIRED*

[Output File](output.txt)