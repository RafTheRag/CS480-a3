/*
 * Author: Rafael Ramirez & Matt D Jaranilla
 * RedID: 825477088 & 825452453
 */

#ifndef PAGETABLE_H
#define PAGETABLE_H

//forward declaratioin
class Level;


class Map {
    public:
        int frameNumber = 0;
        bool validFlag = false;
    
};

//contains class members and functions for PageTable
class PageTable {
    public:

        int levelCount;                                        // Number of levels
        unsigned int* bitmask = new unsigned int[levelCount];      // Bit masks for each level
        unsigned int* shiftAry = new unsigned int[levelCount];     // Number of bits to shift for each level
        unsigned int* entryCount = new unsigned int[levelCount];   // How many entries there should be at each level
        unsigned int* bitsPerLvl = new unsigned int[levelCount];   // Number of bits at each level
        unsigned int* vpns = new unsigned int[levelCount];         // Contains the VPN for each level 
        Level* root;

        
        unsigned int getVPNFromVirtualAddress(unsigned int virtualAddress, unsigned int mask, unsigned int shift);
        void insertVpn2PfnMapping(int frame);
        int findVpn2PfnMapping();
        
        //constructor for page table
        PageTable(int levels, int optind, int argc, char** argv);
       
    
};





#endif