/*
 * Author: Rafael Ramirez & Matt D Jaranilla
 * RedID: 825477088 & 825452453
 */

#ifndef LEVEL_H
#define LEVEL_H

#include "pagetable.h"

// contains class members and functions for Level
class Level{
    public:
        int depth;  // Current depth in the page table hierarchy.
        PageTable* parentTable;  // Pointer to the parent PageTable.
        Map* map;
        Level** nextLevel;

            // Constructor for non-leaf levels
        Level(int depth, PageTable* table);

        long calculateBytesUsed() {
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


        
};

#endif