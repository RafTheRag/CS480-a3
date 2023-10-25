#include <iostream>
#include <fstream>
#include <unistd.h>
#include <vector>
#include <cmath>

#include "vaddr_tracereader.h"
#include "pagetable.h"
#include "pagereplacement.h"
using namespace std;

void generateBitMasks(PageTable& table){
    // cout << table.bitsPerLvl[0] << endl;
    int numOfMaskBits = table.bitsPerLvl[0];
    unsigned int aMask = 1;
    int leftShift = 32;

    for (int i = 0; i < table.levelCount; ++i ){
        numOfMaskBits = table.bitsPerLvl[i];
        aMask = 1;
        for (unsigned int b = 1; b < numOfMaskBits; b++){
            aMask = aMask << 1;
            aMask = aMask | 1;
        }
        leftShift = leftShift - numOfMaskBits;
        // cout << leftShift << endl;
        aMask = aMask << leftShift;
        table.bitmask[i] = aMask;
        
    }

    
    
    // table.bitmask[1] = 15;
}

int main(int argc, char **argv) {

if (argc < 3) {
       throw invalid_argument("Invalid num of arguements");
}


int numMemoryAccesses = 1; // 
int numFrames = 999999; // Default number of frames
int ageThreshold = 10; // Default age threshold
std::string logMode = "summary"; // Default log mode

int option = 0;

while ((option = getopt(argc, argv, "n:f:a:l:")) != -1) {
        switch (option) {
            
            case 'n':
                numMemoryAccesses = atoi(optarg);
                //checks if numOfProgressMarks is greater than 10 to run
                if (numMemoryAccesses < 1){
                    cerr << "Age of last access considered recent must be a number,greater than 0" << endl;
                    exit(EXIT_FAILURE);
                }
                break;

            case 'f':
                numFrames = atoi(optarg);
                //checks if hashmarkInterval is greater than 0 and less than or equal to 10 to run
                if (numFrames < 1) {
                    cerr << "Number of available frames must be a number, greater than 0." << endl;
                    exit(EXIT_FAILURE);
                }
                break;

            case 'a':
                ageThreshold = atoi(optarg);
                if (ageThreshold < 1) {
                    cerr << "Age of last access considered recent must be a number, greater than 0" << endl;
                    exit(EXIT_FAILURE);
                }
                break;

            /*
            * bitmasks – Write out the bitmasks for each level starting with the
            * lowest tree level (root node is at level 0), one per line.
            * va2pa – Show virtual address translation to physical address for
            * every address, one address translation per line 
            * vpns_pfn – For every virtual address, show its virtual page
            * numbers for each level followed by the frame number, one
            * address per line
            * vpn2pfn_pr – For every address, show vpn, pfn, replaced vpn if
            * page replacement happened, and page hit or miss, one address translation per line.
            * offset – Show page offsets of virtual addresses, one address offset per line.
            * summary -  Show summary statistics 
            */ 
            case 'l':
                logMode = atoi(optarg);
                break;

            default:
                cout << "Usage: " << argv[0] << " [-n numMemoryAccesses] [-f numFrames] [-a ageThreshold] [-l logMode] trace.tr readswrites.txt bits_per_lvl " << endl;
                exit(1);
        }
}

/* argv[idx] now has the first mandatory argument: the trace file
path*/
/* argv[idx+1] through argv[argc-1] would be the arguments for
specifying the number of bits for each page table level, one number
per each level */


const char* traceFileName = argv[optind];
FILE* traceFile = fopen(traceFileName, "rb");

if (traceFile == nullptr) {
    std::cerr << "Error: Unable to open the trace file." << std::endl;
    return 1;
}


// ifstream traceFile(argv[optind]);
// if (!traceFile.is_open()){
//     cerr << "Tracefile Unable to open <<" << argv[optind] << ">>" << endl;
//     exit(1);
// }

ifstream readWriteFile(argv[optind + 1]);
if (!readWriteFile.is_open()){
    cerr << "readWriteFile Unable to open <<" << argv[optind+ 1] << ">>" << endl;
    exit(1);
}


PageTable pagetable;


pagetable.levelCount = argc - (optind + 2);
int x = 0;
cout << pagetable.levelCount << endl;
int totalBits = 0;

for (int i = optind + 2; i < argc; ++i){
    pagetable.entryCount[x] = static_cast<unsigned int> (pow(2, atoi(argv[i])));
    pagetable.bitsPerLvl[x] = atoi(argv[i]);
    totalBits += atoi(argv[i]);
    pagetable.shiftAry[x] = totalBits;
    x++;
}
generateBitMasks(pagetable);
// printf("Bitmasks\n");
// printf("level %d mask %08X\n",0, pagetable.bitmask[0]);
// printf("level %d mask %08X\n",1, pagetable.bitmask[1]);
// printf("level %d mask %08X\n",1, pagetable.bitmask[2]);
// printf("level %d mask %08X\n",1, pagetable.bitmask[3]);

//Also correct way but feels pretty bad(Leave for now since I dont know if the first way done will be okay)
// cout << totalBits << endl;
// x = 1;
// pagetable.shiftAry[0] = totalBits;
// for (int i = optind + 2; i < argc; ++i) {
//      totalBits = totalBits -  atoi(argv[i]);
//      pagetable.shiftAry[x] = totalBits;
//     x++;
// }

p2AddrTr addrTrace;
FILE *outputFile = fopen("output.txt", "w");

while (NextAddress(traceFile, &addrTrace)) {
    unsigned int virtualAddress = addrTrace.addr;
    
    AddressDecoder(&addrTrace, outputFile);

    //unsigned int vpn = pagetable.getVPNFromVirtualAddress(virtualAddress, pagetable.bitmask, shift);
    
   

}





return 0;
}