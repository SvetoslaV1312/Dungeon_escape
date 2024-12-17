#ifndef UTILS_H
#define UTILS_H

#pragma once

#include <cstddef> 

// Constants
const size_t mazeSize = 3;
const size_t MazeRows = 4;
const size_t MazeCows = 3;

// Global variables
extern int playerXpos;
extern int playerYpos;
extern int lives;
extern bool won;

// Functions
bool isAlive();
bool isOutOfMaze(int playerXpos, int playerYpos);
void movePlayerUp(char maze[][mazeSize]);
void movePlayer(char maze[][mazeSize], char input);
void printMaze(char maze[][mazeSize]);

#endif // UTILS_H
