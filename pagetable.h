#ifndef PAGETABLE_H
#define PAGETABLE_H

//do I have to use forward declaration
class Level;


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
        Level* root;

        
        unsigned int getVPNFromVirtualAddress(unsigned int virtualAddress, unsigned int mask, unsigned int shift);
        void insertVpn2PfnMapping(unsigned int vpn, int frame);
        Map* findVpn2PfnMapping(unsigned int vpn);
        
        //constructor for page table
        PageTable();
       
    
};





#endif