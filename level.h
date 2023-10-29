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


        
};

#endif