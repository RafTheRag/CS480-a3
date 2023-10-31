/*
 * Author: Rafael Ramirez & Matt D Jaranilla
 * RedID: 825477088 & 825452453
 */
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <vector>
#include <cmath>

#include "vaddr_tracereader.h"
#include "pagetable.h"
#include "pagereplacement.h"
#include "log_helpers.h"
using namespace std;

//Generates bit masks for each level 
// @param reference to parent table
void generateBitMasks(PageTable& table){
    int numOfMaskBits = table.bitsPerLvl[0];
    unsigned int aMask = 1;
    int leftShift = 32;

    for (int i = 0; i < table.levelCount; ++i ){
        numOfMaskBits = table.bitsPerLvl[i];
        aMask = 1;
        for (unsigned int b = 1; b < numOfMaskBits; b++){
            aMask = aMask << 1; //left shift 
            aMask = aMask | 1; //bitwise or with 1  
        }
        leftShift = leftShift - numOfMaskBits;
        aMask = aMask << leftShift; //left shift
        table.bitmask[i] = aMask;
        
    }
}

//Generates offset for each virtual address
// @param address: virtual address, offset: used to shift over a certain amount of bits
int generateOffset(int address, int offset){
    uint32_t original = address;
    uint32_t shiftedAddress = original << offset;
    uint32_t offsetAddress= shiftedAddress >> offset;

    return offsetAddress;
}

//Generates physical address for each virtual address
// @param offset: is the offset of the virtual address, shift: number of bits that is used to shift, frame: frame number correlated to VA 
int generatePhysicalAddress(int offset, int shift, int frame){
    int physicalAddress = 0;
    physicalAddress = frame << shift;
    physicalAddress = physicalAddress | offset;
    
    return physicalAddress;
}

int main(int argc, char **argv) {

//checks if there are a valid number of arguements when declaring your files in the command line
//if invalid throws a invalid exeception
if (argc < 3) {
       throw invalid_argument("Invalid num of arguements");
}


//bunch of variables used to take care of optional arguements
int numMemoryAccesses = -1; // Default to allow the full file read
int numFrames = 999999; // Default number of frames
int ageThreshold = 10; // Default age threshold
std::string logMode = "summary"; // Default log mode
int option = 0;


/*Contains the code for optional arguements for command line
    * n: number of progress marks (either hyphen or #) for displaying 100% progress of a thread execution, default is 50 if not specified.
    * f: place a hash mark “#” in the progress bar every N characters, default is 1
    * a: print number of contained vocab strings to an output file only it is equal to or greater than N, default is 0 if not specified
    * l: types of operations:
    *   bitmasks – Write out the bitmasks for each level starting with the
    *   lowest tree level (root node is at level 0), one per line.
    *   va2pa – Show virtual address translation to physical address for
    *   every address, one address translation per line 
    *   vpns_pfn – For every virtual address, show its virtual page
    *   numbers for each level followed by the frame number, one address per line
    *   vpn2pfn_pr – For every address, show vpn, pfn, replaced vpn if
    *   page replacement happened, and page hit or miss, one address translation per line.
    *   offset – Show page offsets of virtual addresses, one address offset per line.
    *   summary -  Show summary statistics 
    *   else will send a error if usage was not correct 
    */
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

            case 'l':
                logMode = (optarg);
                break;
            

            default:
                cout << "Usage: " << argv[0] << " [-n numMemoryAccesses] [-f numFrames] [-a ageThreshold] [-l logMode] trace.tr readswrites.txt bits_per_lvl " << endl;
                exit(1);
        }
}

// argv[idx] now has the first mandatory argument: the trace file path
const char* traceFileName = argv[optind];
FILE* traceFile = fopen(traceFileName, "rb");

if (traceFile == nullptr) {
    std::cerr << "Error: Unable to open the trace file." << std::endl;
    exit(1);
}

// argv[idx + 1] now has the second mandatory argument: the trace file path
ifstream readWriteFile(argv[optind + 1]);
if (!readWriteFile.is_open()){
    cerr << "readWriteFile Unable to open <<" << argv[optind+ 1] << ">>" << endl;
    exit(1);
}


//Creates an instance of page table and creates the root node(level 0)

int levels = argc - (optind + 2);
PageTable pagetable = PageTable(levels, optind, argc, argv);
PageReplacement circularList = PageReplacement(numFrames, ageThreshold, argv[optind + 1]);

/*int x = 0;
int totalBits = 0;
for (int i = optind + 2; i < argc; ++i){
    pagetable.entryCount[x] = static_cast<unsigned int> (pow(2, atoi(argv[i])));
    pagetable.bitsPerLvl[x] = atoi(argv[i]);
    totalBits += atoi(argv[i]);
    pagetable.shiftAry[x] = totalBits;
    x++;
}*/


generateBitMasks(pagetable);

// calculates the number of bits that need to be shifted to get the offset from VA and the number of bit to get shifted for the vpn
int offset = 0;
int shiftNum = 32;
for (int i = 0; i < pagetable.levelCount; ++i){
    offset = offset + pagetable.bitsPerLvl[i];
    shiftNum = shiftNum - pagetable.bitsPerLvl[i];
}


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
// FILE *outputFile = fopen("output.txt", "w");
int numberOfAddressProcessed = 0;
int pageFrameNum = 0;
int replacedVPN = 0;
bool pageHitorMiss = false;
unsigned int offsetNum = 0;
int shiftBits = 0;
unsigned int virtualAddress = 0;
unsigned int vpn = 0;
int foundFrameNum = 0;
int physicalAddress = 0; 
unsigned int vpnPerLevel = 0;

// loops through each address of the trace file taking care and managing each address to get the offset,
// vpn(s), physical addresses, pageframe number, and more.
while (NextAddress(traceFile, &addrTrace)) {
    
    
    //Checks if number of memory accesses is greater than 1 and if so loops for that amount of addresses
    if (numMemoryAccesses >= 0 && numberOfAddressProcessed >= numMemoryAccesses){
        break;
    }

    // vay to reinstantiate variables in loop
    offsetNum = 0;
    virtualAddress = addrTrace.addr; //sets current address
    // AddressDecoder(&addrTrace, outputFile);
    shiftBits = pagetable.shiftAry[pagetable.levelCount - 1];
    vpn = 0;
    vpnPerLevel = 0;

    //loops through all the levels of the tree (based on amount of optional arguements)
    for (int i = 0; i < pagetable.levelCount; ++i){
        
        vpnPerLevel = pagetable.getVPNFromVirtualAddress(virtualAddress, pagetable.bitmask[i], shiftNum);
        // print_num_inHex(vpnPerLevel);
        

        //Uses the generated vpn for that level and shifts it by the calculated bits
        vpnPerLevel = vpnPerLevel >> (shiftBits - pagetable.shiftAry[i]);
        
        
        pagetable.vpns[i] = vpnPerLevel; //stores the vpns for each level
        
        
        vpn = vpn + pagetable.getVPNFromVirtualAddress(virtualAddress, pagetable.bitmask[i], shiftNum); // calculates the total vpn

    }
    
    
    // if the vpn path is not found it returns -1 and the inserts the vpns into the tree
    // after it increments the pageframe number for the next unfound vpn path
    // else, it find the path and returns the page frame correlated to the vpn
    if (pagetable.findVpn2PfnMapping() == -1){
        // cout << pageFrameNum << endl;
        pagetable.insertVpn2PfnMapping(pageFrameNum);
        pageFrameNum++;
        foundFrameNum = pagetable.findVpn2PfnMapping();

    } else {
        foundFrameNum = pagetable.findVpn2PfnMapping();
        
    }

    Node* node = new Node(vpn);
    int listVpn;
    int listFrame;
    bool replacement = false;
    
    if(!circularList.nodeExists(node) && !circularList.isFull){
        circularList.insertNode(node);
    }
    else if(circularList.isFull && !circularList.nodeExists(node)){
        circularList.replaceNode(node);
        replacement = true;
    }
    node = circularList.getNode(node);

    listFrame = node->frame;
    listVpn = node->vpn;
    pageHitorMiss = node->isHit;
    replacedVPN = node->victimVpn;


    //Calls function that generates offset, and prints offset if logmode
    offsetNum = generateOffset(virtualAddress,offset);
    if (logMode == "offset"){
        print_num_inHex(offsetNum);
    }

    physicalAddress = generatePhysicalAddress(offsetNum, shiftNum, foundFrameNum);
    if (logMode == "va2pa"){
        log_va2pa(virtualAddress, physicalAddress);
    }

    //prints the vpns for each level and the frame correlated to them
    if (logMode == "vpns_pfn"){
        log_vpns_pfn(pagetable.levelCount, pagetable.vpns, foundFrameNum);
    }
    
    //prints out the total vpn, the correlated page frame number, the replaced VPN(if replaced), and whether the pages was already in the table or not
    if (logMode == "vpn2pfn_pr"){
        log_mapping(listVpn, listFrame, replacedVPN, pageHitorMiss);
    }

    numberOfAddressProcessed++; //signifies an address has been processed

}

//generate bitmasks when logmode
if (logMode == "bitmasks"){
    log_bitmasks(pagetable.levelCount, pagetable.bitmask);
}

//generates summart when logmode
else if (logMode == "summary"){

}




return 0;
}