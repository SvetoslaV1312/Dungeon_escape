#include <iostream>
#include <fstream>
#include <windows.h>
#include <stdlib.h>
//#include <string>
#include "play.h"
const size_t MAXLINELENGTH = 100;

void loadLevelToPlay(char* name)
{
    std::cout << "Level is being loaded..." << std::endl;
	int level, lives, coins, mazeRows, mazeColls,key, playerX, playerY;
	bool keyFound;
	char maze[MAZESIZE][MAZESIZE];
    char fileName[MAXLINELENGTH];
    std::ifstream playerFile(fileName); 
    playerFile >> level;
    playerFile >> lives;
    playerFile >> coins;
    playerFile >> key;
    playerFile >> mazeRows;
    playerFile >> mazeColls;
    playerFile >> playerX;
    playerFile >> playerY;
    char* line = new char[mazeColls];
    std::cout << std::endl << level << " " << lives << " " << coins << " " << key;
    for (int i = 0; i < mazeRows; i++) {
        playerFile.getline(line, mazeColls + 1); // Read one row of the maze
        int j = 0;
        char* linePtr = line; // Use a separate pointer to traverse the line

        while (*linePtr) {
            maze[i][j] = *linePtr;
            linePtr++;
            j++;
        }
        maze[i][j] = '\0'; // Null-terminate the string
    }

    std::cout << "If you want to exit press E/e.";
    char input = 'null';
    while (input!='e' )//|| isNotAlive(lives) || hasWon())
    {
        input = getchar();
        system("cls");
        executeMovement(input, maze, playerX, playerY, lives);
        printMovement(maze, mazeRows, mazeColls);
        system("cls");
        
    }

    /*
    while (std::getline(playerFile, line)) //vkarva matrix v file na playera
    {
        savedFile << line << "\n";
    }
    */
}

void executeMovement(char input, char maze[][MAZESIZE], int& playerX, int& playerY, int& lives)
{
    if (input == 'w' || input == 'W')
    {
        if (maze[playerX - 1][playerY] == '#')
        {
            lives--;
            return;
        }
        if (maze[playerX - 1][playerY] == '#')
        {
            lives--;
            return;
        }
        
        maze[playerX][playerY] = '0';

        maze[--playerX][playerY] = '@';
    }
    
}

void printMovement(char maze[][MAZESIZE], int mazeRows, int mazeColls)
{
    for (size_t i = 0; i < mazeRows; i++)
    {
        for (size_t j = 0; j < mazeColls; j++)
        {
            std::cout << maze[i][j];
        }
        std::cout << std::endl;
    }
}

