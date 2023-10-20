#ifndef PAGETABLE_H
#define PAGETABLE_H


typedef struct {
    /**
    * parameters for printing progress bar
    */
    unsigned int numOfProgressMarks;
    unsigned int hashmarkInterval;
    unsigned int minNumOfVocabStringsContainedForPrinting;
    
} SHARED_DATA;

struct Map {
    bool valid;
    int frame;
};

class Level {
public:
    Level(int levels, unsigned int mask, unsigned int shift, int levelNum);
    Level** nextLevel;
    Map* mappings;
    unsigned int mask;
    unsigned int shift;
    int levelNum;
};

class PageTable {
public:
    PageTable(int levels);
    Level* getRootLevel();
private:
    int levels;
    Level* rootLevel;
};

#endif