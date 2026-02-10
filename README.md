# Samir-s-University-Projects
This repository contains some of the projects I have done at university. This includes projects that are purely software based and also embedded systems projects.

# Maze Project

Theseus and the Minotaur – Maze Navigation Simulator (C)

A C program that simulates the Greek myth of Theseus escaping the Labyrinth using deterministic maze-navigation strategies.

The maze is loaded from an external text file and represented as a 2D grid. Theseus (T) must navigate through valid paths (P), avoid walls (W) and the Minotaur (M), and reach the destination (D). Movement is governed by classic maze-solving logic: always turn left, and rotate clockwise when blocked.

Alongside the heuristic approach, the program also computes the optimal shortest path using a breadth-first search (BFS) algorithm, allowing direct comparison between human-style navigation and the mathematically shortest route.

Features

File-based maze loading

Enum-based direction handling (N, E, S, W)

Struct-based state management for clarity and efficiency

Left-hand wall-following navigation strategy

BFS shortest-path calculation

Step-by-step direction tracking

JSON-formatted output for easy parsing and analysis

Output (JSON)

The program reports:

Theseus’ starting coordinates

Number of steps taken using the left-turn strategy

Ordered movement directions

Optimal (shortest) number of steps to the destination

This project focuses on algorithmic problem-solving, structured C programming, and clean separation of logic, while wrapping it all in a mythological theme—because escaping a labyrinth should at least be interesting.
