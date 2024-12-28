#pragma once
//#include <string>

const size_t MAXNAMESIZE = 51;
const size_t MAXLINELENGTH = 100;
const size_t ARRAYSIZE = 30;



// Function to handle player names and levels
char* handlePlayerNameAndGameSession();
void concat(char* fileName, const char* word1, char* word2, const char* word3);
bool checkifPlayed(char name[MAXNAMESIZE]);
void makeNewSession(char* name);
//void loadLevel(char* name);
bool compare(const char* line, const char* name);
int chooseRandomLevel(int level);
void ignoreSeparators(std::ifstream& file);






//void loadPlayerLevel(const std::string& playerName);
//void savePlayerLevel(const std::string& playerName, int level);
//void loadPreviousSession(std::string& name);
