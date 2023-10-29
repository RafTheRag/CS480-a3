/*
 * Author: Rafael Ramirez & Matt D Jaranilla
 * RedID: 825477088 & 825452453
 */

#include "level.h"


//constructor for level, and initializes depth and parenTable varaibles
Level::Level(int depth, PageTable* table) : depth(depth), parentTable(table) {
    
    
    //Creates an array of pointers for each level, 
    nextLevel = new Level*[parentTable->entryCount[depth]];
    for (unsigned int i = 0; i < parentTable->entryCount[depth]; i++) {
        nextLevel[i] = nullptr;
    }
    
    //Map structure array is created when a leaf node is reached
    if (depth == parentTable->levelCount - 1) {
        map = new Map[parentTable->entryCount[depth]];
    }
}