#include <iostream>

#include "utils.h" 

int main()
{
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
    return 0;
}