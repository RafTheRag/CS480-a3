#include "pagetable.h"


Level::Level(int levels, unsigned int mask, unsigned int shift, int levelNum) {
    this->mask = mask;
    this->shift = shift;
    this->levelNum = levelNum;

    // Initialize the next level array
    if (levelNum < levels - 1) {
        nextLevel = new Level*[1 << mask];
        for (int i = 0; i < (1 << mask); i++) {
            nextLevel[i] = nullptr;
        }
    }
    else {
        nextLevel = nullptr;
    }

    // Initialize the mappings array for leaf nodes
    if (levelNum == levels - 1) {
        mappings = new Map[1 << mask];
        for (int i = 0; i < (1 << mask); i++) {
            mappings[i].valid = false;
            mappings[i].frame = -1; // Indicates an invalid frame
        }
    }
}

// Implement the PageTable class
PageTable::PageTable(int levels) {
    this->levels = levels;
//    rootLevel = new Level(levels, /* initial mask */, /* initial shift */, 0);
}

Level* PageTable::getRootLevel() {
    return rootLevel;
}

// Implement additional methods as needed for initializing and accessing the page table
