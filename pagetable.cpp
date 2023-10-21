#include "pagetable.h"


PageTable::PageTable() {
    
    // Initialize the next level array
    // if (levelNum < levels - 1) {
    //     nextLevel = new Level*[1 << mask];
    //     for (int i = 0; i < (1 << mask); i++) {
    //         nextLevel[i] = nullptr;
    //     }
    // }
    // else {
    //     nextLevel = nullptr;
    // }

    // // Initialize the mappings array for leaf nodes
    // if (levelNum == levels - 1) {
    //     mappings = new Map[1 << mask];
    //     for (int i = 0; i < (1 << mask); i++) {
    //         mappings[i].valid = false;
    //         mappings[i].frame = -1; // Indicates an invalid frame
    //     }
    // }
}


// Implement additional methods as needed for initializing and accessing the page table
