#ifndef PAGETABLE_H
#define PAGETABLE_H



class PageTable {
public:

    int levelCount;              // Number of levels
    unsigned int* bitmask = new unsigned int[levelCount];      // Bit masks for each level
    unsigned int* shiftAry = new unsigned int[levelCount];     // Number of bits to shift for each level
    unsigned int* entryCount = new unsigned int[levelCount];

};



#endif