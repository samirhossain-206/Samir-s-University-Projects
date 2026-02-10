# Samir-s-University-Projects
This repository contains some of the projects I have done at university. This includes projects that are purely software based and also embedded systems projects.

## Theseus and the Minotaur – Maze Navigation Simulator (C)

A C program that simulates the Greek myth of **Theseus escaping the Labyrinth** using deterministic maze-navigation strategies.

The maze is loaded from an external text file and represented as a 2D grid. Theseus (`T`) must navigate through valid paths (`P`), avoid walls (`W`) and the Minotaur (`M`), and reach the destination (`D`). Movement is governed by classic maze-solving logic: **always turn left**, and **turn clockwise when blocked**.

In parallel, the program computes the **optimal shortest path** using a Breadth-First Search (BFS) algorithm, allowing direct comparison between heuristic navigation and the mathematically shortest route.

### Features
- Loads maze layout from an external text file
- 2D character-array maze representation
- Enum-based direction handling (N, E, S, W)
- Struct-based position and state management
- Left-hand wall-following navigation strategy
- BFS-based shortest path calculation
- Step-by-step direction tracking
- JSON-formatted output for easy parsing

### Output (JSON)
The program outputs:
- Theseus’ starting coordinates
- Number of steps taken using the left-turn strategy
- Ordered list of movement directions
- Optimal (shortest) number of steps to the destination

This project demonstrates **structured C programming, algorithmic problem-solving, and clean separation of logic**, wrapped in a mythological theme where escaping the Labyrinth is harder than it looks.
