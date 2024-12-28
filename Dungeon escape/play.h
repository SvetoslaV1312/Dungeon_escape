#pragma once

#pragma once
#include <string>
#include <windows.h>
#include <stdlib.h>
#include <fstream>


const size_t MAZESIZE = 30;


void loadLevelToPlay(char* name);
void executeMovement(char input, char maze[][MAZESIZE], int& playerX, int& playerY, int& lives);
void printMovement(char maze[][MAZESIZE], int mazeRows, int mazeColls);

