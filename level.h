#ifndef LEVEL_H
#define LEVEL_H

#include "pagetable.h"

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