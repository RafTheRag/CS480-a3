/*
 * Author: Rafael Ramirez & Matt D Jaranilla
 * RedID: 825477088 & 825452453
 */

#include <string>

#ifndef PAGEREPLACEMENT_H
#define PAGEREPLACEMENT_H
//Class declaration for a node in the circular list. It contains important information for identification.
class Node{
    public:
        Node* next = nullptr;
        int vpn = -1;
        int victimVpn = -1;
        int frame = -1;
        int lastAccesedTime = -1;
        bool isDirty = false;
        bool isHit = false;

        Node(int vpn); //consturctor for the node class.
};

//Decleration of the pageReplacement class which includes the head of the circular list and data that keeps track of important information needed for a page replacement.
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

        PageReplacement(int maxSize, int ageLimit, std::string readWriteFile);  //Constructor for pagereplacement class which takes in the max amount fo frames in the list, the agelimit for replacement, and the file that indicates reads and writes.
        void insertNode(Node* node); //Inserts a node into the circular list.
        bool  nodeExists(Node* node); //returns wheter a given node is found in the circular list.
        Node* getNode(Node* node); //retrive the given node from the circular list.
        void replaceNode(Node* replacementNode); //replaces node when circular list is full.
};


#endif
