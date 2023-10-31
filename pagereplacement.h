#include <string>

#ifndef PAGEREPLACEMENT_H
#define PAGEREPLACEMENT_H

class Node{
    public:
        Node* next = nullptr;
        int vpn = -1;
        int victimVpn = -1;
        int frame = -1;
        int lastAccesedTime = -1;
        bool isDirty = false;
        bool isHit = false;

        Node(int vpn);
};

class PageReplacement{
    public:
        Node* head = nullptr;
        std::string readWriteFile;
        char* actions;
        int clockHand = 0;
        int maxSize;
        int time = 0;
        int ageLimit;
        bool isFull = false;

        PageReplacement(int maxSize, int ageLimit, std::string readWriteFile);
        void insertNode(Node* node);
        bool  nodeExists(Node* node);
        Node* getNode(Node* node);
        void replaceNode(Node* replacementNode);
};




#endif