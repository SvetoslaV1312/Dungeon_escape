#include <iostream>
#include <fstream>
#include<cstdlib>
#include<ctime>

//#include <cstring> // For strlen
#include "profiles.h"

//const size_t MAXNAMESIZE = 51;
//const size_t MAXLINELENGTH = 100;

char* handlePlayerNameAndGameSession() {
    std::cout << "If you have an account press 1. \nIf you want to register press 0: ";
    int registered;
    std::cin >> registered;
    std::cin.ignore();

    static char name[MAXNAMESIZE]; // what if longer??
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
            return handlePlayerNameAndGameSession();
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
    if (previouslyPlayed) {
        std::cout << "Press 1 to continue previous level or press 0 to start a new level: ";
        int choice;
        std::cin >> choice;
        std::cin.ignore(); 
        if (choice == 0) {
            makeNewSession(name);
        }
        else if (choice == 1) {
            std::cout << "Loading previous session...\n";
        }
        else {
            std::cout << "Wrong input" << std::endl;
        }
    }
    else {
        makeNewSession(name);
    }
    return name;
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
   // while (*fileName) { fileName++; }

    while (*word1) {
        *fileName = *word1;
        fileName++;
        word1++;
    }
    while (*word2) {
        *fileName = *word2;
        fileName++;
        word2++;
    }
    while (*word3) {
        *fileName = *word3;
        fileName++;
        word3++;
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
    std::cin >> level;
    if (level < 1 || level>3) {
        std::cout << "Wrong number" << std::endl;
        return makeNewSession(name);
    }
    int variantNum=chooseRandomLevel(level);
    int lives, coins, mazeRows, mazeCols, playerX, playerY;
    int key;
    char maze[ARRAYSIZE][ARRAYSIZE] = { 0 }; 
    char premadeFileName[MAXLINELENGTH] = {0}; //eg Level1variation3.txt
    concat(premadeFileName, "Level", level+'0');
    concat(premadeFileName, "variation", 3 + '0');//set for now to 3 should be !!!!!variationNum
    concat(premadeFileName, ".txt", '\0');

    //printf("%s\n", premadeFileName); // Output: Level1variation3.txt

    //std::cout << premadeFileName << std::endl;
    char playerFileName[MAXLINELENGTH] = {0};
    concat(playerFileName, "player", name, ".txt");//good


    //snprintf(playerFileName, MAXLINELENGTH, "player_%s.txt", name);//ot neta

    std::ifstream premadeFile(premadeFileName);
    if (!premadeFile) {
        std::cerr << "Error: Could not open premade level file.\n";
        return;
    }

    // Read level, lives, coins, maze dimensions, and maze data
    premadeFile >> level;
    premadeFile >> lives;
    premadeFile >> coins;
    premadeFile >> key;
    premadeFile >> mazeRows;
    premadeFile >> mazeCols;
    premadeFile >> playerX;
    premadeFile >> playerY;
    ignoreSeparators(premadeFile);

   // premadeFile.ignore(); // Skip newl

    for (int i = 0; i < mazeRows; i++) {
        premadeFile.getline(maze[i], mazeCols + 1); //  one row of the maze
    }

    premadeFile.close();

    // Open the player's file for writing
    std::ofstream playerFile(playerFileName);
    if (!playerFile) {
        std::cerr << "Error: Could not open player file for writing.\n";
        return;
    }

    // Write the data to the player's file
    playerFile << level << std::endl;
    playerFile << lives << std::endl;
    playerFile << coins << std::endl;
    playerFile << key << std::endl;;
    playerFile << mazeRows << std::endl;
    playerFile << mazeCols << std::endl;
    playerFile << playerX << std::endl;
    playerFile << playerY << std::endl;

    for (int i = 0; i < mazeRows; i++) {
        playerFile << maze[i] << std::endl;//check if works
    }

    playerFile.close();

    std::cout << "Player file created successfully with level data.\n";
}


int chooseRandomLevel(int level)
{
        srand(time(0));
        return  rand() % 3;
}

/*
void loadLevel(char* name) {
    char filename[MAXLINELENGTH];
    concat(filename, "player", name, ".txt");
    std::ofstream savedFile(filename);
    if (!savedFile) {
        std::cerr << "Error: Could not open " << filename << " for writing.\n";
        return;
    }
    savedFile << "New session data\n"; // Placeholder for actual level data
    savedFile.close();
}


    std::string name;
    std::cout << "Enter your name: ";
    std::cin >> name;

    std::ifstream nameFile("Player_names.txt");
    bool nameFound = false;

    if (nameFile) {
        std::string line;
        while (std::getline(nameFile, line)) {
            if (line == name) {
                nameFound = true;
                break;
            }
        }
    }
    nameFile.close();

    if (!nameFound) {
        std::ofstream outFile("Player_names.txt", std::ios::app);
        if (!outFile) {
            std::cerr << "Error: Could not open Player_names.txt for writing.\n";
            return;
        }
        outFile << name << std::endl;
        outFile.close();
        std::cout << "Welcome, " << name << "! You've been added as a new player.\n";
    }
    else {
        std::cout << "Welcome back, " << name << "!\n";
    }
    



void loadPlayerLevel(const std::string& playerName) {
    std::string fileName = "player_" + playerName + ".txt";
    std::ifstream saveFile(fileName);
    int lastLevel;

    if (!saveFile) {
        std::cout << "No save data found. Please choose a level between 1 and 3.\n";
        std::cin >> lastLevel;
        std::ofstream saveFile(fileName);
    }

    saveFile >> lastLevel;
    saveFile.close();

    std::cout << "Last level played: " << lastLevel << ".\n";
}

void savePlayerLevel(const std::string& playerName, int level) {
    std::string fileName = "player_" + playerName + ".txt";
    std::ofstream saveFile(fileName);

    if (!saveFile) {
        std::cerr << "Error: Could not open " << fileName << " for writing.\n";
        return;
    }

    saveFile << level;
    saveFile.close();

    std::cout << "Progress saved. Current level: " << level << ".\n";
}
*/