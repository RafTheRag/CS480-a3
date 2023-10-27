#include "pagetable.h"
#include "level.h"

PageTable::PageTable(){
    root = new Level(0, this);
}

unsigned int PageTable::getVPNFromVirtualAddress(unsigned int virtualAddress, unsigned int mask, unsigned int shift) {
    unsigned int vpn = (virtualAddress & mask) >> shift;
    return vpn;
}

void PageTable::insertVpn2PfnMapping(unsigned int vpn, int frame) {
    // Implement the logic to insert/update the mapping in the page table
    // based on the provided VPN and frame (PFN).
}

// Mandatory interface 3: findVpn2PfnMapping
// Map* PageTable::findVpn2PfnMapping(unsigned int vpn) {
//     // Implement the logic to find and return the mapping for the given VPN.
//     // Return NULL or an invalid frame number if the mapping is not found or not valid.
//     // You can define the Map structure as required and return it here.
// }
    


// Implement additional methods as needed for initializing and accessing the page table
