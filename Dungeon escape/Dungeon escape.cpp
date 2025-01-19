/**
*Solution to course project # <3>
*Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia
University
* Winter semester 2024 / 2025
* @author ‹Svetoslav Tsvyatkov>
*@idnumber ‹9MI0600427>
*@compiler <VC GCC>
*/

#include <iostream>
#include <fstream>
#include "profiles.h" 
#include "play.h" 
int main()
{
    char name[MAXNAMESIZE] = {};
    handlePlayerNameAndGameSession(name);
    loadLevelAndPlay(name);
    return 0;
}
