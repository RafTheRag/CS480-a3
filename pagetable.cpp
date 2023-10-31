/*
 * Author: Rafael Ramirez & Matt D Jaranilla
 * RedID: 825477088 & 825452453
 */

#include "pagetable.h"
#include "level.h"
#include <iostream>
#include <fstream>
#include <cmath>

//Constructor for PageTable
PageTable::PageTable(int levels, int optind, int argc, char** argv) : levelCount(levels){

    int x = 0;
    int totalBits = 0;
    for (int i = optind + 2; i < argc; ++i){
        entryCount[x] = static_cast<unsigned int> (pow(2, atoi(argv[i])));
        bitsPerLvl[x] = atoi(argv[i]);
        totalBits += atoi(argv[i]);
        shiftAry[x] = totalBits;
        x++;
    }

    root = new Level(0, this);
    
}

//Generates the virtual address for vpn's for each level by using the bitmask for each level and then shifting the bits
unsigned int PageTable::getVPNFromVirtualAddress(unsigned int virtualAddress, unsigned int mask, unsigned int shift) {
    unsigned int vpn = (virtualAddress & mask) >> shift;
    return vpn;
}

void PageTable::insertVpn2PfnMapping(int frame) {
    Level* currentLevel = root;
    unsigned int index = 0;

    //iterates through all the levels and inserts the vpn correlated to the level
    for (int level = 0; level < levelCount - 1; ++level) {
        // std::cout << vpns[level] << std::endl;
        //if nextLevel is null, creates a new level if it doesn't exist.
        if (currentLevel->nextLevel[vpns[level]] == nullptr) {

            currentLevel->nextLevel[vpns[level]] = new Level(level + 1, this);
        }
        currentLevel = currentLevel->nextLevel[vpns[level]];
    }
    // At the leaf level, the map structure is updated
    index = vpns[levelCount - 1];
    // std::cout << index << std::endl;
    currentLevel->map[index].frameNumber = frame;
    currentLevel->map[index].validFlag = true;
}
 
// Function searches through the tree to check if the level index exists. If not returns -1, and executes the
// function to insert the vpn into the tree. 
int PageTable::findVpn2PfnMapping() {
    Level* currentLevel = root;
    for (int level = 0; level < levelCount - 1; ++level) {
        
        if (currentLevel->nextLevel[vpns[level]] == nullptr) {
            return -1; // Mapping does not exist.
        }
        currentLevel = currentLevel->nextLevel[vpns[level]];
    }
    // At the leaf level, return the mapping.
    int index = vpns[levelCount - 1];
    if (currentLevel->map[index].validFlag) {
        return (currentLevel->map[index].frameNumber);
    } else {
        return -1;
    }
}