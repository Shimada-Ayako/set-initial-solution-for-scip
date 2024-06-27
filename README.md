# set-initial-solution-for-scip
Demonstrate SCIP with an initail solution using C language.

<!-- Badges -->
<table>
    <tr>
        <td>License</td>
        <td>Lang</td>
        <td>Solver</td>
        <td>Editor</td>
    </tr>
    <tr>
        <td>
            <img src="http://img.shields.io/badge/license-MIT-blue.svg?style=flat">
        </td>
        <td>
            <img src="https://img.shields.io/badge/-C-6699CB.svg?logo=c">
        </td>
        <td>
            <img src="https://img.shields.io/badge/-SCIP-FFFFFF.svg?">
        </td>
        <td>
            <img src="https://img.shields.io/badge/-VSCode-007ACC.svg?logo=visualstudiocode">
        </td>
    </tr>
</table>

# Overview
[SCIP](https://www.scipopt.org) is a solver for integer programming and constraint programming.
Due to its ease of use, SCIP solver have been widely applied 
in various areas including academic research and 
industrial applications.
However, there is limited information on using 
the SCIP solver with the C language, particularly regarding 
how to add an initial solution.

This project demonstrates the method of using the SCIP solver with C language for integer programming problems. Specifically, it shows how to add an initial solution using C language.

In main.c, we take the knapsack problem as an example and demonstrate how to call the SCIP solver with C language. First, we solve the knapsack problem (knapsack1), then use its solution as the initial solution to solve the same knapsack problem again (knapsack2).

Through this example, we will show the usage of SCIP with C language and how to add an initial solution.



# Install 
This project requires [SCIP](https://www.scipopt.org). Please see the documentation for more details.

# Usage
This package entails following steps:
## 1. build
```
mkdir build  
cmake -S . -B build
cd build
make
```

## 2. solve the problem
```
./main <number of items>  <limit of knapsack>
```


# Example
```
./main 10 60                                                                                                              
feasible solution found by trivial heuristic after 0.0 seconds, objective value 6.000000e+01
presolving:
presolving (1 rounds: 1 fast, 0 medium, 0 exhaustive):
 0 deleted vars, 0 deleted constraints, 0 added constraints, 0 tightened bounds, 0 added holes, 0 changed sides, 0 changed coefficients
 0 implications, 0 cliques
transformed 2/2 original solutions to the transformed problem space
Presolving Time: 0.00

SCIP Status        : problem is solved [optimal solution found]
Solving Time (sec) : 0.00
Solving Nodes      : 0
Primal Bound       : +6.00000000000000e+01 (2 solutions)
Dual Bound         : +6.00000000000000e+01
Gap                : 0.00 %
Optimal solution found:
second time
The initial solution satisfies all constraints.
successfully
nconss = 1
1/1 feasible solution given by solution candidate storage, new primal bound 6.000000e+01

presolving:
presolving (1 rounds: 1 fast, 0 medium, 0 exhaustive):
 0 deleted vars, 0 deleted constraints, 0 added constraints, 0 tightened bounds, 0 added holes, 0 changed sides, 0 changed coefficients
 0 implications, 0 cliques
transformed 2/2 original solutions to the transformed problem space
Presolving Time: 0.00

SCIP Status        : problem is solved [optimal solution found]
Solving Time (sec) : 0.00
Solving Nodes      : 0
Primal Bound       : +6.00000000000000e+01 (2 solutions)
Dual Bound         : +6.00000000000000e+01
Gap                : 0.00 %
Optimal solution found:
```

# License
The source code is licensed MIT.


