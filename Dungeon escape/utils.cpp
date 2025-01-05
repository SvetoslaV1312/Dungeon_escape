#include "utils.h"  
#include <iostream>
#include <windows.h>
/*
//const size_t mazeSize = 3, MazeRows = 4, MazeCows = 3;
int playerXpos = 2, playerYpos = 1, lives = 3;
bool won = false;

bool isAlive() {
    return lives != 0;
}

bool isOutOfMaze(int playerXpos, int playerYpos)
{
    return playerXpos < 0 || playerYpos>MazeRows || playerYpos < 0 || playerXpos>MazeCows;
}
void movePlayerUp(char maze[][mazeSize])
{
    if (maze[playerXpos - 1][playerYpos] == '#')
    {
        lives--;
        return;
    }
    if (maze[playerXpos - 1][playerYpos] == '#')
    {
        lives--;
        return;
    }
    if (isOutOfMaze(playerXpos - 1, playerYpos))
    {
        won = true;
        maze[playerXpos][playerYpos] = '0';
        playerXpos--;
        return;
    }
    maze[playerXpos][playerYpos] = '0';

    maze[--playerXpos][playerYpos] = '@';
}


void  movePlayer(char maze[][mazeSize], char input)
{
    if (input == 'w' || input == 'W')
        movePlayerUp(maze);

}

void printMaze(char maze[][mazeSize])
{
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            std::cout << maze[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

*/