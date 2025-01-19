/**
*Solution to course project # <3>
*Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia
University
* Winter semester 2024 / 2025
* @author ‹Svetoslav Tsvyatkov>
*@idnumber ‹9MI0600427>
*@compiler <VC GCC>
*‹Handles player account and level creation>
*/


#include <iostream>
#include <fstream>
#include<cstdlib>
#include<ctime>
#include "profiles.h"

char* handlePlayerNameAndGameSession(char* name) {
    system("cls");
    std::cout << "If you have an account press 1. \nIf you want to register press 0: ";
    int registered=0;
    while (true)
    {
        std::cin >> registered;
        if ((registered == 0 || registered == 1) && std::cin.good())
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "You eneterd wrong. Try again entering a valid number. " << std::endl;
    }
    if (registered == 1) {
        std::cout << "Enter your name: ";
        std::cin.getline(name, MAXNAMESIZE);
        std::ifstream nameFile("Player_names.txt");
        bool nameFound = false;

        if (nameFile) {
            char line[MAXLINELENGTH];
            while (nameFile.getline(line, MAXLINELENGTH)) { 
                if (compare(line, name)) {
                    nameFound = true;
                    break;
                }
            }
        }
        nameFile.close();

        if (!nameFound) {

            std::cout << "Login was not successful." << std::endl;
            //std::this_thread::sleep_for(std::chrono::seconds(2));
            return handlePlayerNameAndGameSession(name);
        }
    }
    else if (registered == 0) {
        std::cout << "Enter your name: ";
        std::cin.getline(name, MAXNAMESIZE);
        std::ofstream outFile("Player_names.txt", std::ios::app);
        if (!outFile) {
            std::cerr << "Error: Could not open Player_names.txt for writing.\n";
            return nullptr;
        }
        outFile << name << std::endl;
        outFile.close();
        std::cout << "Welcome, " << name << "! You've been added as a new player.\n";
    }
    else {
        std::cout << "Wrong input" << std::endl;
        return nullptr;
    }
    bool previouslyPlayed = checkifPlayed(name);
    concat(name, "player", name, ".txt");
    if (previouslyPlayed) {
        std::cout << "Press 1 to continue previous level or press 0 to start a new level: ";
        int choice;
        while (true)
        {
            std::cin >> choice;
            if ((choice == 0 || choice == 1) && std::cin.good())
            {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "You eneterd wrong. Try again entering a valid number. " << std::endl;
        }

        if (choice == 0) {
            makeNewSession(name);
            return name;
        }
        else if (choice == 1) {
            std::cout << "Loading previous session...\n";
            return name;
        }
        else {
            std::cout << "Wrong input" << std::endl;
        }
    }
    else {
        makeNewSession(name);
        return name;
    }
}

bool compare(const char* line, const char* name) {
    while (*line && *line != '\n' && *name && *name != '\n') {
        if (*line != *name) return false;
        line++;
        name++;
    }
    return *line == '\0' && *name == '\0';
}

void concat(char* fileName, const char* word1,  char* word2, const char* word3) {
    char temp[MAXLINELENGTH] = { 0 }; 
    char* tempPtr = temp; 

    while (*word1) {
        *tempPtr = *word1;
        tempPtr++;
        word1++;
    }

    while (*word2) {
        *tempPtr = *word2;
        tempPtr++;
        word2++;
    }

    while (*word3) {
        *tempPtr = *word3;
        tempPtr++;
        word3++;
    }

    *tempPtr = '\0'; 

    tempPtr = temp; 
    while (*tempPtr) {
        *fileName = *tempPtr;
        fileName++;
        tempPtr++;
    }
    *fileName = '\0'; 
}

void concat(char* fileName, const char* word1, char symbol) {
    while (*fileName) { fileName++; }
    while (*word1) {
        *fileName = *word1;
        fileName++;
        word1++;
    }
    *fileName = symbol;
    fileName++;
    *fileName = '\0';
}

bool checkifPlayed(char name[MAXNAMESIZE]) {
    char fileName[MAXLINELENGTH];
    concat(fileName, "player", name, ".txt");
    std::ifstream savedFile(fileName);
    return savedFile.good();
}

void ignoreSeparators(std::ifstream& file) {
    while (file.peek() == ' ' || file.peek() == '\t' || file.peek() == '\n' || file.peek() == '\r') {
        file.ignore();
    }
}
void makeNewSession(char* name) {   
    std::cout << "Choose your level from 1 to 3: ";
    int level;
    while (true)
    {
        std::cin >> level;
        if ((level >= 1 && level <= 3) && std::cin.good())
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "You eneterd wrong. Try again entering a valid number. " << std::endl;
    }
    int variantNum=chooseRandomLevel(level);
    int lives, coins, mazeRows, mazeCols, playerX, playerY, portalCount, steppedOnChest, steppedOnPortal;
    int key;
    char maze[ARRAYSIZE][ARRAYSIZE] = { 0 }; 
    char premadeFileName[MAXLINELENGTH] = {0}; //eg Level1variation3.txt
    concat(premadeFileName, "Level", level+'0');
    concat(premadeFileName, "variation", variantNum + '0');
    concat(premadeFileName, ".txt", '\0');

   
   char*  playerFileName = name;
   


    std::ifstream premadeFile(premadeFileName);
    if (!premadeFile) {
        std::cerr << "Error: Could not open premade level file.\n";
        return;
    }

    premadeFile >> level;
    premadeFile >> lives;
    premadeFile >> coins;
    premadeFile >> key;
    premadeFile >> mazeRows;
    premadeFile >> mazeCols;
    premadeFile >> playerX;
    premadeFile >> playerY;
    premadeFile >> steppedOnChest;
    premadeFile >> steppedOnPortal;
    premadeFile >> portalCount;
    int arrayOfPortals[10][2][2];
    for (int i = 0; i < portalCount; i++) {
            premadeFile >> arrayOfPortals[i][0][0];
            premadeFile >> arrayOfPortals[i][0][1];
    }
    ignoreSeparators(premadeFile);

    for (int i = 0; i < mazeRows; i++) {
        premadeFile.getline(maze[i], mazeCols + 1); 
    }

    premadeFile.close();

    std::ofstream playerFile(playerFileName);
    if (!playerFile) {
        std::cerr << "Error: Could not open player file for writing.\n";
        return;
    }

    playerFile << level << std::endl;
    playerFile << lives << std::endl;
    playerFile << coins << std::endl;
    playerFile << key << std::endl;;
    playerFile << mazeRows << std::endl;
    playerFile << mazeCols << std::endl;
    playerFile << playerX << std::endl;
    playerFile << playerY << std::endl;
    playerFile << steppedOnChest << std::endl;
    playerFile << steppedOnPortal << std::endl;
    playerFile << portalCount << std::endl;

    for (int i = 0; i < portalCount; i++) {
        playerFile << arrayOfPortals[i][0][0] << std::endl;;
        playerFile << arrayOfPortals[i][0][1] << std::endl;;
    }

    for (int i = 0; i < mazeRows; i++) {
        playerFile << maze[i] << std::endl;
    }

    playerFile.close();

    std::cout << "Player file created successfully with level data.\n";
}


void seedRandomGenerator() {
    srand(unsigned int(time(0)));
}

int chooseRandomLevel(int level) {
    seedRandomGenerator();
    return (rand() % 3) + 1; 
}


void saveProgress(char* name, int level, int  lives, int coins, int mazeRows, int mazeColls, int key, int playerX, int playerY, int portalCount, bool steppedOnPortal, bool hasWon, bool steppedOnChest,
    char maze[ARRAYSIZE][ARRAYSIZE], int arrayOfPortals[MAXPORTALS][2][2])
{
    std::ofstream playerFile(name);
    if (!playerFile) {
        std::cerr << "Error: Could not open player file for saving.\n";
        return;
    }
    playerFile << level << std::endl;
    playerFile << lives << std::endl;
    playerFile << coins << std::endl;
    playerFile << key << std::endl;;
    playerFile << mazeRows << std::endl;
    playerFile << mazeColls << std::endl;
    playerFile << playerX << std::endl;
    playerFile << playerY << std::endl;
    playerFile << steppedOnChest << std::endl;
    playerFile << steppedOnPortal << std::endl;
    playerFile << portalCount << std::endl;

    for (int i = 0; i < portalCount; i++) {
        playerFile << arrayOfPortals[i][0][0] << std::endl;;
        playerFile << arrayOfPortals[i][0][1] << std::endl;;
    }

    for (int i = 1; i <= mazeRows; i++) {
        playerFile << maze[i] << std::endl;
    }

    playerFile.close();

    std::cout << "Player file saved successfully with level data.\n";
}

