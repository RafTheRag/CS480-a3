#include "Level.h"
#include "PageTable.h"

Level::Level(int depth, PageTable* table) : depth(depth), parentTable(table) {
    // Initialize nextLevel array in the member initializer list.
    nextLevel = new Level*[parentTable->entryCount[depth]];

    for (int i = 0; i < parentTable->entryCount[depth]; i++) {
        nextLevel[i] = nullptr;
    }
}