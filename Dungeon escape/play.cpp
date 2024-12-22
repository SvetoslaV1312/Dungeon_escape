#include <iostream>
#include <fstream>
#include <string>
#include "play.h"

const size_t MAXLINELENGTH = 100;

void play(char* name)
{
	int level, lives, coins, mazeRows, mazeColls;
	bool keyFound;
	char maze[ARRAYSIZE][ARRAYSIZE];
    char fileName[MAXLINELENGTH];
    std::ifstream playerFile(fileName);
    playerFile >> level;
    playerFile >> lives;
    playerFile >> coins;
    playerFile >> mazeRows;
    playerFile >> mazeColls;
    char* line = new char[mazeColls];

    for (int i = 0; i < mazeRows; i++)
    {
        int j=0;
        playerFile.getline(line, mazeColls);
        
            while (*line)
            {
                maze[i][j] = *line;
                line++;
                j++;
            }
    }

    /*
    while (std::getline(playerFile, line)) //vkarva matrix v file na playera
    {
        savedFile << line << "\n";
    }
    */
}
