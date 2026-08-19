# MFTSP Routing Heuristics

This repository contains C++ implementations of heuristic methods developed for experiments with a multi-family routing problem.

The project was developed as part of my research in routing and combinatorial optimization and includes constructive procedures, local-search methods, perturbation operators, and computational experiments on benchmark instances.

## Main methods

The implementation includes different components used to build and improve routing solutions, including:

- nearest-neighbor based construction;
- 2-opt improvement;
- local search;
- perturbation procedures;
- VNS-related experiments;
- parallel execution experiments using OpenMP.

## Implementation

The project is implemented in C++.

Main files:

- `principal.cpp` — main experimental program;
- `biblioteca_profe_claudio.h` — problem structures and routing procedures;
- `biblioteca_perturbacoes.h` — local-search and perturbation procedures.

The code was developed as a research prototype, so some parameters and instance paths are configured directly in the source code.

## Instances

The experiments use routing benchmark instances derived from classical TSP datasets, including examples based on:

- Burma14
- Bayg29
- Att48
- Bier127
- A280
- GR666

Different instance configurations are used to represent families, vehicles, and visit requirements.

## Technologies

- C++
- OpenMP
- Heuristic optimization
- Local search
- Vehicle routing
- Combinatorial optimization

## Research context

This repository represents an earlier stage of my work with routing algorithms and heuristic optimization.

My more recent research focuses on exact optimization methods, column generation, and branch-and-price for vehicle routing and offshore logistics.

## Author

**Dieferson Flori Massarotto**

Operations Research & Simulation Engineer  
PhD in Naval and Ocean Engineering — University of São Paulo
