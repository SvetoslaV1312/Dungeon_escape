#pragma once

#pragma once
#include <string>
#include <windows.h>
#include <stdlib.h>
#include <fstream>
#include <limits> 
const size_t MAZESIZE = 30;
const size_t MAXPORTAL = 10;

void loadLevelAndPlay(char* name);
void executeMovement(char input, char maze[][MAZESIZE], int& playerX, int& playerY,
int& lives, int& coins, int arrayOfPortals[MAXPORTAL][2][2],
int& key, int portalCount, bool& steppedOnPortal, bool& hasWon, bool& steppedOnChest);
void movePlayerRight(char  maze[][MAZESIZE], int& playerX, int& playerY, int& lives, bool& steppedOnChest, bool& traveledToPortal, int& coins, int& key, bool& hasWon, int portalCount, int  arrayOfPortals[MAXPORTAL][2][2]);
void movePlayerDown(char maze[][MAZESIZE], int& playerX, int& playerY, int& lives, bool& steppedOnChest, bool& traveledToPortal, int& coins, int& key, bool& hasWon, int portalCount, int  arrayOfPortals[MAXPORTAL][2][2]);
void teleportFunction(size_t& i, int portalCount, bool& steppedOnChest, char  maze[][MAZESIZE], int& playerX, int& playerY, bool& traveledToPortal, int  arrayOfPortals[MAXPORTAL][2][2]);
void movePlayerLeft(char  maze[][MAZESIZE], int& playerX, int& playerY, int& lives, bool& steppedOnChest, bool& traveledToPortal, int& coins, int& key, bool& hasWon, int portalCount, int  arrayOfPortals[MAXPORTAL][2][2]);
void movePlayerUp(char  maze[][MAZESIZE], int& playerX, int& playerY, int& lives, bool& steppedOnChest, bool& traveledToPortal, int& coins, int& key, bool& hasWon, int portalCount, int  arrayOfPortals[MAXPORTAL][2][2]);
void printMovement(char maze[][MAZESIZE], int mazeRows, int mazeColls, int lives, int level, int key, int coins);
bool checkProgress(char input, int  lives, bool hasWon);

