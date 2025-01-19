/**
*Solution to course project # <3>
*Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia
University
* Winter semester 2024 / 2025
* @author ‹Svetoslav Tsvyatkov>
*@idnumber ‹9MI0600427>
*@compiler <VC GCC>
*‹Handels the loading of the game and the gameplay itself>
*/


#include <iostream>
#include <fstream>
#include <windows.h>
#include <stdlib.h>
#include <limits> 
#include "play.h"
#include "profiles.h" 


void loadLevelAndPlay(char* name)
{
    int level, lives, coins, mazeRows, mazeColls, key, playerX, playerY, portalCount;
    bool steppedOnPortal, hasWon = false, steppedOnChest;
    char maze[MAZESIZE][MAZESIZE];
    std::ifstream playerFile(name);
    if (!playerFile) {
        std::cerr << "Error: Could not open playerFile.txt for reading.\n";
        return;
    }
    playerFile >> level;
    if (level == -858993460)//undefined
    {
        std::cerr << "Unsucessful load of previous session."<<std::endl;
        makeNewSession(name);
        loadLevelAndPlay(name);
    }
    std::cout << "Level is being loaded..." << std::endl;
    playerFile >> lives;
    playerFile >> coins;
    playerFile >> key;
    playerFile >> mazeRows;
    playerFile >> mazeColls;
    playerFile >> playerX;
    playerFile >> playerY;
    playerFile >> steppedOnChest;
    playerFile >> steppedOnPortal;
    playerFile >> portalCount;
    int arrayOfPortals[MAXPORTAL][2][2];
    for (int i = 0; i < portalCount; i++) {
        playerFile >> arrayOfPortals[i][0][0];
        playerFile >> arrayOfPortals[i][0][1];
    }
    char* line = new char[mazeColls+1];
    for (int i = 0; i < mazeRows+1; i++) {
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
    delete[] line;

    system("cls");
    char input = ' ';
    while (checkProgress(input, lives, hasWon))
    {
        printMovement(maze, mazeRows, mazeColls, lives, level, key, coins);
        std::cout << std::endl << std::endl<< "If you want to exit press E/e." << std::endl;

        std::cin >> input;

        system("cls");
        executeMovement(input, maze, playerX, playerY, lives,
            coins, arrayOfPortals, key, portalCount, steppedOnPortal, hasWon, steppedOnChest);

    }
    if (input == 'e') saveProgress(name, level, lives, coins, mazeRows, mazeColls, key, playerX, playerY, portalCount, steppedOnPortal, hasWon, steppedOnChest,
        maze, arrayOfPortals);
    else if (lives == 0)
    {
        std::cout << "You have lost";
        std::ofstream file(name, std::ios::trunc);
    }
    else if (hasWon) {
        std::cout << "Congrats you have won";
        std::ofstream file(name, std::ios::trunc);
    }


}

bool checkProgress(char input, int  lives, bool hasWon)
{
    if (lives == 0) return false;
    else if (input == 'e') return false;
    else if (hasWon) return false;
    return true;
}


void executeMovement(char input, char maze[][MAZESIZE], int& playerX, int& playerY,
    int& lives, int& coins, int arrayOfPortals[MAXPORTAL][2][2],
    int& key, int portalCount, bool& traveledToPortal, bool& hasWon, bool& steppedOnChest)
{
    if (input == 'w' || input == 'W')
    { 
      movePlayerUp( maze, playerX, playerY, lives, steppedOnChest,traveledToPortal, coins, key, hasWon, portalCount, arrayOfPortals);
    }
    else if (input == 'a' || input == 'A') {
        movePlayerLeft(maze, playerX, playerY, lives, steppedOnChest, traveledToPortal, coins, key, hasWon, portalCount, arrayOfPortals);
    }
    else if (input == 's' || input == 'S') {
        movePlayerDown(maze, playerX, playerY, lives, steppedOnChest, traveledToPortal, coins, key, hasWon, portalCount, arrayOfPortals);
    }
    else if (input == 'd' || input == 'D') {
        movePlayerRight(maze, playerX, playerY, lives, steppedOnChest, traveledToPortal, coins, key, hasWon, portalCount, arrayOfPortals);
    }


}

void movePlayerRight(char  maze[][MAZESIZE], int& playerX, int& playerY, int& lives, bool& steppedOnChest, bool& traveledToPortal, int& coins, int& key, bool& hasWon, int portalCount, int  arrayOfPortals[MAXPORTAL][2][2])
{
    if (maze[playerX][playerY + 1] == '#') {
        lives--;
        return;
    }
    else if (maze[playerX][playerY + 1] == ' ') {
        if (steppedOnChest) {
            maze[playerX][playerY] = 'x';
            maze[playerX][++playerY] = '@';
            steppedOnChest = false;
        }
        else if (traveledToPortal) {
            maze[playerX][playerY] = '%';
            maze[playerX][++playerY] = '@';
            traveledToPortal = false;
        }
        else {
            maze[playerX][playerY] = ' ';
            maze[playerX][++playerY] = '@';
        }
    }
    else if (maze[playerX][playerY + 1] == 'c') { // coin
        coins++;
        if (steppedOnChest) {
            maze[playerX][playerY] = 'x';
            maze[playerX][++playerY] = '@';
            steppedOnChest = false;
        }
        else if (traveledToPortal) {
            maze[playerX][playerY] = '%';
            maze[playerX][++playerY] = '@';
            traveledToPortal = false;
        }
        else {
            maze[playerX][playerY] = ' ';
            maze[playerX][++playerY] = '@';
        }
    }
    else if (maze[playerX][playerY + 1] == '&') { // key
        key++;
        if (steppedOnChest) {
            maze[playerX][playerY] = 'x';
            maze[playerX][++playerY] = '@';
            steppedOnChest = false;
        }
        else if (traveledToPortal) {
            maze[playerX][playerY] = '%';
            maze[playerX][++playerY] = '@';
            traveledToPortal = false;
        }
        else {
            maze[playerX][playerY] = ' ';
            maze[playerX][++playerY] = '@';
        }
    }
    else if (maze[playerX][playerY + 1] == 'x') { // chest
        if (key == 1) {
            hasWon = 1;
            return;
        }
        else {
            maze[playerX][playerY] = ' ';
            maze[playerX][++playerY] = '@';
            steppedOnChest = true;
        }
    }
    else {
        for (size_t i = 0; i < portalCount; i++) {
            if (playerX == arrayOfPortals[i][0][0] && playerY + 1 == arrayOfPortals[i][0][1]) {
                teleportFunction(i, portalCount, steppedOnChest, maze, playerX, playerY, traveledToPortal, arrayOfPortals);

            }
        }
    }
}

void movePlayerDown(char  maze[][MAZESIZE], int& playerX, int& playerY, int& lives, bool& steppedOnChest, bool& traveledToPortal, int& coins, int& key, bool& hasWon, int portalCount, int  arrayOfPortals[MAXPORTAL][2][2])
{
    if (maze[playerX + 1][playerY] == '#') {
        lives--;
        return;
    }
    else if (maze[playerX + 1][playerY] == ' ') {
        if (steppedOnChest) {
            maze[playerX][playerY] = 'x';
            maze[++playerX][playerY] = '@';
            steppedOnChest = false;
        }
        else if (traveledToPortal) {
            maze[playerX][playerY] = '%';
            maze[++playerX][playerY] = '@';
            traveledToPortal = false;
        }
        else {
            maze[playerX][playerY] = ' ';
            maze[++playerX][playerY] = '@';
        }
    }
    else if (maze[playerX + 1][playerY] == 'c') { // coin
        coins++;
        if (steppedOnChest) {
            maze[playerX][playerY] = 'x';
            maze[++playerX][playerY] = '@';
            steppedOnChest = false;
        }
        else if (traveledToPortal) {
            maze[playerX][playerY] = '%';
            maze[++playerX][playerY] = '@';
            traveledToPortal = false;
        }
        else {
            maze[playerX][playerY] = ' ';
            maze[++playerX][playerY] = '@';
        }
    }
    else if (maze[playerX + 1][playerY] == '&') { // key
        key++;
        if (steppedOnChest) {
            maze[playerX][playerY] = 'x';
            maze[++playerX][playerY] = '@';
            steppedOnChest = false;
        }
        else if (traveledToPortal) {
            maze[playerX][playerY] = '%';
            maze[++playerX][playerY] = '@';
            traveledToPortal = false;
        }
        else {
            maze[playerX][playerY] = ' ';
            maze[++playerX][playerY] = '@';
        }
    }
    else if (maze[playerX + 1][playerY] == 'x') { // chest
        if (key == 1) {
            hasWon = 1;
            return;
        }
        else {
            maze[playerX][playerY] = ' ';
            maze[++playerX][playerY] = '@';
            steppedOnChest = true;
        }
    }
    else {
        for (size_t i = 0; i < portalCount; i++) {
            if (playerX + 1 == arrayOfPortals[i][0][0] && playerY == arrayOfPortals[i][0][1]) {
                teleportFunction(i, portalCount, steppedOnChest, maze, playerX, playerY, traveledToPortal, arrayOfPortals);
            }
        }
    }
}

void movePlayerLeft(char  maze[][MAZESIZE], int& playerX, int& playerY, int& lives, bool& steppedOnChest, bool& traveledToPortal, int& coins, int& key, bool& hasWon, int portalCount, int  arrayOfPortals[MAXPORTAL][2][2])
{
    if (maze[playerX][playerY - 1] == '#') {
        lives--;
        return;
    }
    else if (maze[playerX][playerY - 1] == ' ') {
        if (steppedOnChest) {
            maze[playerX][playerY] = 'x';
            maze[playerX][--playerY] = '@';
            steppedOnChest = false;
        }
        else if (traveledToPortal) {
            maze[playerX][playerY] = '%';
            maze[playerX][--playerY] = '@';
            traveledToPortal = false;
        }
        else {
            maze[playerX][playerY] = ' ';
            maze[playerX][--playerY] = '@';
        }
    }
    else if (maze[playerX][playerY - 1] == 'c') { // coin
        coins++;
        if (steppedOnChest) {
            maze[playerX][playerY] = 'x';
            maze[playerX][--playerY] = '@';
            steppedOnChest = false;
        }
        else if (traveledToPortal) {
            maze[playerX][playerY] = '%';
            maze[playerX][--playerY] = '@';
            traveledToPortal = false;
        }
        else {
            maze[playerX][playerY] = ' ';
            maze[playerX][--playerY] = '@';
        }
    }
    else if (maze[playerX][playerY - 1] == '&') { // key
        key++;
        if (steppedOnChest) {
            maze[playerX][playerY] = 'x';
            maze[playerX][--playerY] = '@';
            steppedOnChest = false;
        }
        else if (traveledToPortal) {
            maze[playerX][playerY] = '%';
            maze[playerX][--playerY] = '@';
            traveledToPortal = false;
        }
        else {
            maze[playerX][playerY] = ' ';
            maze[playerX][--playerY] = '@';
        }
    }
    else if (maze[playerX][playerY - 1] == 'x') { // chest
        if (key == 1) {
            hasWon = 1;
            return;
        }
        else {
            maze[playerX][playerY] = ' ';
            maze[playerX][--playerY] = '@';
            steppedOnChest = true;
        }
    }
    else {
        for (size_t i = 0; i < portalCount; i++) {
            if (playerX == arrayOfPortals[i][0][0] && playerY - 1 == arrayOfPortals[i][0][1]) {
                teleportFunction(i, portalCount, steppedOnChest, maze, playerX, playerY, traveledToPortal, arrayOfPortals);
            }
        }
    }
}

void movePlayerUp( char  maze[][MAZESIZE], int& playerX, int& playerY, int& lives, bool& steppedOnChest, bool& traveledToPortal, int& coins, int& key, bool& hasWon, int portalCount, int  arrayOfPortals[MAXPORTAL][2][2])
{
        if (maze[playerX - 1][playerY] == '#') {
            lives--;
            return;
        }
        else if (maze[playerX - 1][playerY] == ' ') {
            if (steppedOnChest) {
                maze[playerX][playerY] = 'x';
                maze[--playerX][playerY] = '@';
                steppedOnChest = false;
            }
            else if (traveledToPortal) {
                maze[playerX][playerY] = '%';
                maze[--playerX][playerY] = '@';
                traveledToPortal = false;
            }
            else {
                maze[playerX][playerY] = ' ';
                maze[--playerX][playerY] = '@';
            }
        }
        else if (maze[playerX - 1][playerY] == 'c') { // coin
            coins++;
            if (steppedOnChest) {
                maze[playerX][playerY] = 'x';
                maze[--playerX][playerY] = '@';
                steppedOnChest = false;
            }
            else if (traveledToPortal) {
                maze[playerX][playerY] = '%';
                maze[--playerX][playerY] = '@';
                traveledToPortal = false;
            }
            else {
                maze[playerX][playerY] = ' ';
                maze[--playerX][playerY] = '@';
            }
        }
        else if (maze[playerX - 1][playerY] == '&') { // key
            key++;
            if (steppedOnChest) {
                maze[playerX][playerY] = 'x';
                maze[--playerX][playerY] = '@';
                steppedOnChest = false;
            }
            else if (traveledToPortal) {
                maze[playerX][playerY] = '%';
                maze[--playerX][playerY] = '@';
                traveledToPortal = false;
            }
            else {
                maze[playerX][playerY] = ' ';
                maze[--playerX][playerY] = '@';
            }
        }
        else if (maze[playerX - 1][playerY] == 'x') { // chest
            if (key == 1) {
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
            for (size_t i = 0; i < portalCount; i++) {
                if (playerX - 1 == arrayOfPortals[i][0][0] && playerY == arrayOfPortals[i][0][1]) {
                    teleportFunction(i, portalCount, steppedOnChest, maze, playerX, playerY, traveledToPortal, arrayOfPortals);
                }
            }
        }
   
}

void teleportFunction(size_t& i, int portalCount, bool& steppedOnChest, char  maze[][MAZESIZE], int& playerX, int& playerY, bool& traveledToPortal, int  arrayOfPortals[MAXPORTAL][2][2])
{
    if (i == portalCount - 1) i = -1;
    if (steppedOnChest) {
        maze[playerX][playerY] = 'x';
        steppedOnChest = false;
    }
    traveledToPortal = true;
    maze[playerX][playerY] = ' ';
    playerX = arrayOfPortals[i + 1][0][0];
    playerY = arrayOfPortals[i + 1][0][1];
    maze[playerX][playerY] = '@';
}

void printMovement(char maze[][MAZESIZE], int mazeRows, int mazeColls, int lives, int level, int key, int coins)
{
    std::cout << "Level: " << level << std::endl;
    std::cout << "Lives: " << lives << std::endl;
    std::cout << "Coins: " << coins << std::endl;
    std::cout << "Key: ";
    if (!key)
    {
        std::cout << "key not found" << std::endl;
    }
    else   std::cout << "key found" << std::endl;

    for (size_t i = 1; i < mazeRows+1; i++)
    {
        for (size_t j = 0; j < mazeColls; j++)
        {
            std::cout << maze[i][j];
        }
        std::cout << std::endl;
    }
}
