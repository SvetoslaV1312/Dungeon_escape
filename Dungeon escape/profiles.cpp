#include <iostream>
#include <fstream>
#include <string>

void randomLoad(int level)
{

}


void chooseLevel(std::string name)
{
    std::cout << "Enter a number between 1 and 3 to pick level"<<std::endl;
    int level;
    std::cin >> level;
    if (level < 1 || level >3)
    {
        std::cout << "Unexpected input." << std::endl;
        chooseLevel(name);
    }
    else if (level == 1)
    {
        randomLoad(level);
    }
}


void handlePlayerNames() {
    std::string name;
    std::cout << "Enter your name: ";
    std::cin >> name;

    std::string filePath = "C:/Users/Svetoslav Tsvyatkov/source/repos/Dungeon escape/Player_names.txt";

    // TODO fix it for normal palyer_names
    std::ifstream MyReadFile(filePath);
    if (!MyReadFile) {
        std::cerr << "Error: Could not open file for reading. Make sure Player_names.txt exists!\n";
        return;
    }

    std::string line;
    bool nameFound = false;

    while (std::getline(MyReadFile, line)) {
        if (line == name) {
            nameFound = true;
            break;
        }
    }
    MyReadFile.close();

    if (!nameFound) {
        std::ofstream MyFile(filePath, std::ios::app); // Append mode
        if (!MyFile) {
            std::cerr << "Error: Could not open file for writing.\n";
            return;
        }

        MyFile << name << std::endl;
        MyFile.close();
        chooseLevel(name);
    }
    else {
        std::cout << "Welcome back.\n";
    }
}




