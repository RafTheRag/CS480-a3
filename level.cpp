/*
 * Author: Rafael Ramirez & Matt D Jaranilla
 * RedID: 825477088 & 825452453
 */

#include "level.h"
#include <iostream>


//constructor for level, and initializes depth and parenTable varaibles
Level::Level(int depth, PageTable* table) : depth(depth), parentTable(table) {
    
    
    //Creates an array of pointers for each level, 
    nextLevel = new Level*[parentTable->entryCount[depth]];
    //std::cout << "First Check: " << parentTable->entryCount[0] << std::endl;
    for (unsigned int i = 0; i < parentTable->entryCount[depth]; i++) {
        nextLevel[i] = nullptr;
    }
    
    //Map structure array is created when a leaf node is reached
    //std::cout << "Second Check: " << depth << " : " << parentTable->levelCount - 1 << std::endl;
    if (depth == parentTable->levelCount - 1) {
        map = new Map[parentTable->entryCount[depth]];
    }
}