#ifndef PAGETABLE_H
#define PAGETABLE_H





typedef struct {
    int frameNumber;
    bool validFlag;
}Map;


class PageTable {
    public:

        int levelCount = 0;                                            // Number of levels
        unsigned int* bitmask = new unsigned int[levelCount];      // Bit masks for each level
        unsigned int* shiftAry = new unsigned int[levelCount];     // Number of bits to shift for each level
        unsigned int* entryCount = new unsigned int[levelCount];
        unsigned int* bitsPerLvl = new unsigned int[levelCount];
        
        
        unsigned int getVPNFromVirtualAddress(unsigned int virtualAddress, unsigned int mask, unsigned int shift);
        void insertVpn2PfnMapping(unsigned int vpn, int frame);
        // Map* findVpn2PfnMapping(unsigned int vpn);
        

        typedef struct Level{
            int depth;  // Current depth in the page table hierarchy.
            PageTable* parentTable;  // Pointer to the parent PageTable.
            int numEntries;
            // Constructor for non-leaf levels
            Level(){
                // Initialize nextLevel array.
            

                Level** nextLevel = new Level*[parentTable->entryCount[depth]];


                for (int i = 0; i < numEntries; i++) {
                    nextLevel[i] = nullptr;
                }
            }

            // // Constructor for leaf levels
            // Level(int depth, PageTable* parent, int mapSize) : depth(depth), parentTable(parent) {
            //     // Initialize map array.
            //     map = new Map[mapSize];
            // }
        } Level;

        Level* root;
    
};




#endif