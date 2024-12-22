#include <iostream>
#include <fstream>
#include "utils.h" 
#include "profiles.h" 
#include "play.h" 

/*
void  play(std::string fileName)
{
    load(fileName, chosenlevel);
    maze = filename;
    char movemnt;
    std::cin >> movemnt;

    while (isAlive || movemnt=='e') //e=exit
    {
        std::cin >> movemnt;
        movePlayer(maze,movemnt);
        printMaze(maze);
        saveprogess(maze);
    }
}
*/
int main()
{
    char* pickedPlayer=handlePlayerNameAndGameSession();
    concat(pickedPlayer, "player", handlePlayerNameAndGameSession(), ".txt");
    play(pickedPlayer);
    //play("player_" + name + ".txt");


    /*
    char myFirstMaze[4][3] =
    { {'0', '0','0'},
      {'0', '0','0'},
      {'0', '@','0'},
      {'0', '#','0'} };
    char input = 'a';
    while (input != 0 && isAlive() && !won)
    {
        std::cin >> input;
        movePlayer(myFirstMaze, input);
        printMaze(myFirstMaze);
    }
    if (isOutOfMaze) std::cout << "you won";
    if (!isAlive()) std::cout << "you die";
    */
    return 0;
}