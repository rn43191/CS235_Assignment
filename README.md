# CS235_Assignment
Artificial Intelligence Assignments

***Assignment 1:*** Problem Solving 8-Queens problem using Uniform Cost Search
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
***Assignment 2:***
Problem Solving Travelling Salesman using A* Heuristic Search
*Assumption : Each city is connected to every other city i.e., complete graph.*
- Initial State: 
Agent in the start city and has not visited any other city
- Edge-cost: 
distance between the cities represented by the nodes, use this cost to calculate g(n).
- h(n): 
distance to the nearest unvisited city from the current city + estimated distance to travel all the unvisited cities (MST heuristic used here) + nearest distance from an unvisited city to the start city. 
- Goal State:
Agent has visited all the cities and reached the start city again
