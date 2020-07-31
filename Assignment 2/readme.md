## Problem Solving Travelling Salesman using A* Heuristic Search

*Assumption : Each city is connected to every other city i.e., complete graph.*
- Initial State: 
Agent in the start city and has not visited any other city
- Edge-cost: 
distance between the cities represented by the nodes, use this cost to calculate g(n).
- h(n): 
distance to the nearest unvisited city from the current city + estimated distance to travel all the unvisited cities (MST heuristic used here) + nearest distance from an unvisited city to the start city. 
- Goal State:
Agent has visited all the cities and reached the start city again
---
### Compilation

```
g++ TSP.cpp
./a.out
```
---
## I/O Files

[Input File](input.txt)

[Output File](output.txt)