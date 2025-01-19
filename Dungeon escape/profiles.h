#pragma once
//#include <string>

const size_t MAXNAMESIZE = 51;
const size_t MAXLINELENGTH = 100;
const size_t ARRAYSIZE = 30;
const size_t MAXPORTALS = 30;


char* handlePlayerNameAndGameSession(char* name);
void concat(char* fileName,const  char* word1, char* word2, const char* word3);
bool checkifPlayed(char name[MAXNAMESIZE]);
void makeNewSession(char* name);
bool compare(const char* line, const char* name);
int chooseRandomLevel(int level);
void ignoreSeparators(std::ifstream& file);
void saveProgress(char* name, int level, int  lives, int coins, int mazeRows, int mazeColls, int key, int playerX, int playerY, int portalCount, bool traveledToPortal, bool hasWon, bool steppedOnChest,
char maze[ARRAYSIZE][ARRAYSIZE], int arrayOfPortals[MAXPORTALS][2][2]);
void seedRandomGenerator();
