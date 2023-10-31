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
    for (unsigned int i = 0; i < parentTable->entryCount[depth]; i++) {
        nextLevel[i] = nullptr;
    }
    
    //Map structure array is created when a leaf node is reached
    if (depth == parentTable->levelCount - 1) {
        map = new Map[parentTable->entryCount[depth]];
    }
}

long Level::calculateBytesUsed(){
    long bytesUsed = sizeof(*this);  // Add the size of the Level object itself

     // Add the size of the children array
    bytesUsed += sizeof(*nextLevel) * parentTable->entryCount[depth];

    // If this is not a leaf level, traverse the children
    if (depth < parentTable->levelCount - 1) {
        for (unsigned int i = 0; i < parentTable->entryCount[depth]; i++) {
            if (nextLevel[i] != nullptr) {
                bytesUsed += nextLevel[i]->calculateBytesUsed();
            }
        }
    }

    // If this is a leaf level, add the size of the map
    if (depth == parentTable->levelCount - 1) {
        bytesUsed += sizeof(*map) * parentTable->entryCount[depth];
    }

    return bytesUsed;
}