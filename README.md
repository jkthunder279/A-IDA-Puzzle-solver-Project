# A-IDA-Puzzle-solver-Project
# 8-Puzzle Solver using A* and IDA*


This project solves the classic **8-puzzle problem** using:

- **A\*** (with Manhattan Distance heuristic)
- **IDA\*** (Iterative Deepening A\*)

Includes both a **C++ terminal version** and a **Python Pygame GUI** for visualization.

---

## Features

- Solves any valid 8-puzzle input.
- A* visualization with step-by-step animation.
- Efficient IDA* with depth-first, memory-optimized search.
- Clean, modular code (C++ and Python).

---

## 📌 Algorithms

### A* (A-Star)
- Best-first search using `f(n) = g(n) + h(n)`
- Uses Manhattan Distance as heuristic.
- Maintains explored and frontier sets.
- **Optimal and complete**, but memory-intensive.

### IDA* (Iterative Deepening A*)
- Combines DFS with A*’s heuristic.
- Iteratively increases threshold (`f = g + h`).
- Reuses memory: **space complexity = O(depth)**.
- Slightly slower due to re-expansion, but more memory-efficient.

---

## Sample Run

**Initial State:**
0 2 3
4 5 6
7 1 8

**Goal State:**
1 2 3
4 5 6
7 8 0

**Sample IDA* Output:**
Solved in 8 moves
Path: D R D L U R D R

## Complexity

Algorithm	Time Complexity	Space Complexity
A*	O(b^d)	O(b^d)
IDA*	O(b^d)	O(d)

b = branching factor (max 4 for 8-puzzle => (4)^d)

d = depth of optimal solution
