#pragma once

#pragma once
#include <string>
#include <windows.h>
#include <stdlib.h>
#include <fstream>
#include <limits> 


const size_t MAZESIZE = 30;


void loadLevelToPlay(char* name);
void executeMovement(char input, char maze[][MAZESIZE], int& playerX, int& playerY,
    int& lives, int& coins, int arrayOfPortals[10][2][2],
    int& key, int portalCount, bool& traveledToPortal, bool& hasWon, bool& steppedOnChest);
void printMovement(char maze[][MAZESIZE], int mazeRows, int mazeColls);

