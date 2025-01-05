#include <iostream>
#include <fstream>
#include <windows.h>
#include <stdlib.h>
#include <limits> 
//#include <string>
#include "play.h"
const size_t MAXLINELENGTH = 100;

void loadLevelToPlay(char* name)
{
    std::cout << "Level is being loaded..." << std::endl;
	int level, lives, coins, mazeRows, mazeColls,key, playerX, playerY, portalCount;
    bool traveledToPortal = false, hasWon = false, steppedOnChest=false;
	char maze[MAZESIZE][MAZESIZE];
    std::ifstream playerFile(name);
    if (!playerFile) {
        std::cerr << "Error: Could not open playerFile.txt for reading.\n";
        return;
    }
    playerFile >> level;
    playerFile >> lives;
    playerFile >> coins;
    playerFile >> key;
    playerFile >> mazeRows;
    playerFile >> mazeColls;
    playerFile >> playerX;
    playerFile >> playerY;
    playerFile >> portalCount;
    int arrayOfPortals[10][2][2];
    for (int i = 0; i < portalCount; i++) {
        playerFile >> arrayOfPortals[i][0][0];
        playerFile >> arrayOfPortals[i][0][1];
    }
    char* line = new char[mazeColls];
    //!!!!playerFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); fix the i=1 in print func
    //std::cout << std::endl << level << " " << lives << " " << coins << " " << key;
    for (int i = 0; i < mazeRows; i++) {
        playerFile.getline(line, mazeColls + 1); // Read one row of the maze
        int j = 0;
        char* linePtr = line; 

        while (*linePtr) {
            maze[i][j] = *linePtr;
            linePtr++;
            j++;
        }
        maze[i][j] = '\0'; 
    }
    std::cout << "If you want to exit press E/e.";
    char input = 'null';
    while (input!='e' )//|| isNotAlive(lives) || hasWon())
    {
        std::cin >> input;
        system("cls");
        //input = getchar();
        //system("cls");
        executeMovement(input, maze, playerX, playerY, lives, 
            coins, arrayOfPortals, key, portalCount, traveledToPortal, hasWon, steppedOnChest);
        printMovement(maze, mazeRows, mazeColls);
        //system("cls");
        
    }
    delete[] line;


    /*
    while (std::getline(playerFile, line)) //vkarva matrix v file na playera
    {
        savedFile << line << "\n";
    }
    */
}

void executeMovement(char input, char maze[][MAZESIZE], int& playerX, int& playerY,
    int& lives, int& coins, int arrayOfPortals[10][2][2],
    int& key, int portalCount, bool& traveledToPortal, bool& hasWon, bool& steppedOnChest)
{
    if (input == 'w' || input == 'W')
    {
        
        if (maze[playerX - 1][playerY] == '#')
        {
            lives--;
            return;
        }
 
        else if (maze[playerX - 1][playerY] == ' ')
        {
            if (steppedOnChest) {
                maze[playerX][playerY] = 'x';
                maze[--playerX][playerY] = '@';
                steppedOnChest = false;
            }
            else if (traveledToPortal)
            {
                maze[playerX][playerY] = '%';
                maze[--playerX][playerY] = '@';
                traveledToPortal = false;
            }
            else
            {
                maze[playerX][playerY] = ' ';
                maze[playerX][playerY] = '@';
            }
        }
        else if (maze[playerX - 1][playerY] == 'c')//coin
        {
            coins++;
            if (steppedOnChest) {
                maze[playerX][playerY] = 'x';
                maze[--playerX][playerY] = '@';
                steppedOnChest = false;
            }
            else if (traveledToPortal)
            {
                maze[playerX][playerY] = '%';
                maze[--playerX][playerY] = '@';
                traveledToPortal = false;
            }
            else
            {
                maze[playerX][playerY] = ' ';
                maze[--playerX][playerY] = '@';
            }
        }
        else if (maze[playerX - 1][playerY] == '&')//key
        {
            key++;
            if (steppedOnChest) {
                maze[playerX][playerY] = 'x';
                maze[--playerX][playerY] = '@';
                steppedOnChest = false;
            }
            else if (traveledToPortal)
            {
                maze[playerX][playerY] = '%';
                maze[--playerX][playerY] = '@';
                traveledToPortal = false;
            }
            else
            {
                maze[playerX][playerY] = ' ';
                maze[--playerX][playerY] = '@';
            }
        }
        else if (maze[playerX - 1][playerY] == 'x')//chest
        {
            if (key==1)
            {
                hasWon = 1;
                return;
            }
            else {
                maze[playerX][playerY] = ' ';
                maze[--playerX][playerY] = '@';
                steppedOnChest = true;
            }
            
        }
        else {
            for (size_t i = 0; i < portalCount; i++)
            {
                if (playerX - 1 == arrayOfPortals[i][0][0] && playerY == arrayOfPortals[i][0][1])
                {
                     if (steppedOnChest)
                     {
                         maze[playerX][playerY] = 'x';
                         steppedOnChest = false;
                     }
                     traveledToPortal = true;
                     playerX = arrayOfPortals[i + 1][0][0];
                     playerY = arrayOfPortals[i + 1][0][1];
                     maze[playerX][playerY] = '@';
                     break;
                }
            }
        }

    }
    
}

void printMovement(char maze[][MAZESIZE], int mazeRows, int mazeColls)
{
    for (size_t i = 1; i < mazeRows; i++)
    {
        for (size_t j = 0; j < mazeColls; j++)
        {
            std::cout << maze[i][j];
        }
        std::cout << std::endl;
    }
}

