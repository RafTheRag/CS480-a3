#ifndef PAGETABLE_H
#define PAGETABLE_H



class PageTable {
public:

    int levelCount = 0;                                            // Number of levels
    unsigned int* bitmask = new unsigned int[levelCount];      // Bit masks for each level
    unsigned int* shiftAry = new unsigned int[levelCount];     // Number of bits to shift for each level
    unsigned int* entryCount = new unsigned int[levelCount];
    Level* root;
    PageTable(int levels) : levelCount(levels) {
        // Initialize bitmaskAry, shiftAry, entryCount based on your requirements.
        // Allocate the root node.
        root = new Level(0, this);
    }
    unsigned int getVPNFromVirtualAddress(unsigned int virtualAddress, unsigned int mask, unsigned int shift);
    void insertVpn2PfnMapping(unsigned int vpn, int frame);
    Map* findVpn2PfnMapping(unsigned int vpn);

};

// class Level {
// public:
//     Level** nextLevel; // Array of pointers to the next level
//     // Map* mappings;     // Array of mappings (VPN to PFN)
//     int numEntries;    // Number of entries in this level

//     // Constructor for interior levels
//     Level(int entries);

//     // Constructor for leaf levels
//     Level(int entries, bool isLeaf);

//     ~Level(); // Destructor to release memory
// };

struct Level {
    int depth;  // Current depth in the page table hierarchy.
    PageTable* parentTable;  // Pointer to the parent PageTable.
    
    // For non-leaf levels
    Level** nextLevel;  // Array of pointers to the next level (interior nodes).
    
    // For leaf levels
    Map* map;  // Array of Map objects for mapping virtual pages to physical frames.

    // Constructor for non-leaf levels
    Level(int depth, PageTable* parent) : depth(depth), parentTable(parent) {
        // Initialize nextLevel array.
        nextLevel = new Level*[parentTable->entryCount[depth]];
        for (int i = 0; i < parentTable->entryCount[depth]; i++) {
            nextLevel[i] = nullptr;
        }
    }

    // Constructor for leaf levels
    Level(int depth, PageTable* parent, int mapSize) : depth(depth), parentTable(parent) {
        // Initialize map array.
        map = new Map[mapSize];
    }
};

struct Map {
    int frameNumber;
    bool validFlag;
};


#endif