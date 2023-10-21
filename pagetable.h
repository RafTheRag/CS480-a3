#ifndef PAGETABLE_H
#define PAGETABLE_H



class PageTable {
public:

    int levelCount;              // Number of levels
    unsigned int* bitmask = new unsigned int[levelCount];      // Bit masks for each level
    unsigned int* shiftAry = new unsigned int[levelCount];     // Number of bits to shift for each level
    unsigned int* entryCount = new unsigned int[levelCount];
    // Level* rootNodePtr; 

};

class Level {
public:
    Level** nextLevel; // Array of pointers to the next level
    // Map* mappings;     // Array of mappings (VPN to PFN)
    int numEntries;    // Number of entries in this level

    // Constructor for interior levels
    Level(int entries);

    // Constructor for leaf levels
    Level(int entries, bool isLeaf);

    ~Level(); // Destructor to release memory
};

class Map {
public:
    bool isValid;
    int frameNumber;
};


#endif