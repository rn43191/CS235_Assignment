**Grouping n students having random marks in m subjects into k groups such that each group has minimum diversity.**

- *Chromosome*: Generate random marks of N student in M subjects.

- *Population*: Randomly select any 50 chromosome for Init population which is divided into K groups and Group Representative is Average value of that group.

- *Fitness Value*: Take absolute value of difference of group representative and student's marks.

- *Selection*: Select 2 parent by Tournament Selection.

- *Crossover*: Choose a random point and execute single point crossover.

- *Mutation*: Randomly select a gene from each chromosome of the crossover population and mutating with random group representative to increase diversity.
---
### Compilation

```
g++ kmeans.cpp
./a.out
```
---
## I/O Files

[Input File](input.txt)

[Output File](output.txt)