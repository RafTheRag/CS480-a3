#include <iostream>
#include <fstream>
#include <unistd.h>
#include <vector>

#include "vaddr_tracereader.h"
#include "pagetable.h"
#include "pagereplacement.h"
using namespace std;

int main(int argc, char **argv) {

if (argc < 3) {
       throw invalid_argument("Invalid num of arguements");
}


int numMemoryAccesses = 1; // Initialize to -1 to indicate it's not specified
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
                if (numFrames < 1) {
                    cerr << "Age of last access considered recent must be a number, greater than 0" << endl;
                    exit(EXIT_FAILURE);
                }
                break;

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


ifstream traceFile(argv[optind]);
traceFile.open(argv[optind]);
if (!traceFile){
    cerr << "Tracefile Unable to open <<" << argv[optind] << ">>" << endl;
    exit(1);
}

ifstream readWriteFile(argv[optind + 1]);
readWriteFile.open(argv[optind + 1]);
if (!readWriteFile){
    cerr << "readWriteFile Unable to open <<" << argv[optind+ 1] << ">>" << endl;
    exit(1);
}

std::vector<int> levelBits;

if (optind + 2 < argc)
{
  
}




return 0;
}