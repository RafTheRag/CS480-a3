/*
 * Author: Rafael Ramirez & Matt D Jaranilla
 * RedID: 825477088 & 825452453
 */

#include "pagereplacement.h"
#include <fstream>
#include <iostream>

Node::Node(int vpn) : vpn(vpn){}

//initiates the pagereplacement class and creates an array the size of the readwrites file which contains a character array of all characters in the file.
PageReplacement::PageReplacement(int maxSize, int ageLimit, std::string readWriteFile) : maxSize(maxSize), ageLimit(ageLimit), readWriteFile(readWriteFile){

    std::fstream file(readWriteFile);
    file.seekg(0, std::ios::end);
    std::streampos fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    actions = new char[fileSize];

    file.read(actions, fileSize);
    file.close();

}

//insert a node into the circular list. This also inserts for an empty circular list and it updates the according values to keep track.
void PageReplacement::insertNode(Node* node){

    //insertion for empty list
    if(head == nullptr){
        node->lastAccesedTime = time;
        node->frame = clockHand;
        if(!node->isDirty && (actions[time] - '0')) node->isDirty = true;
        head = node;
        clockHand++;
        time++;
        return;
    }

    Node* currentNode = head;

    //traverses list until currentNode has no pointer to next node. Given node is then assigned to the next node
    while(currentNode->next){
        currentNode = currentNode->next;
    }
    node->lastAccesedTime = time;
    node->frame = clockHand;
    if(!node->isDirty && (actions[time] - '0')) node->isDirty = true;
    currentNode->next = node;
    clockHand++;
    time++;

    //If our clock reaches the max size then it must be rest back to 0
    if(clockHand >= maxSize){
        isFull = true;
        node->next = head;
        clockHand = 0;
    }
}

//Checks to see if the given node exists and if it does it means it was inserted therefore we update node values to reflect that.
bool PageReplacement::nodeExists(Node* node){

    Node* currentNode = head;

    //traverses list until we either encounter a nullptr or we make a full rotation around the list.
    while(currentNode != nullptr && currentNode->next != head){

        //if our currentNode has the same vpn as the given node then given node exists in list.
        if(currentNode->vpn == node->vpn){
            currentNode->isHit = true;
            currentNode->victimVpn = -1;
            if(!currentNode->isDirty && (actions[time] - '0')) currentNode->isDirty = true;
            currentNode->lastAccesedTime = time;
            time++;
            return true;
        }
        currentNode = currentNode->next;
    }

    return false;
}

//returns the given node from the circular list. this is used to retirve the important information from the node in main.
Node* PageReplacement::getNode(Node* node){
    Node* currentNode = head;

    while(currentNode){
        if(currentNode->vpn == node->vpn){
            return currentNode;
        }
        currentNode = currentNode->next;
    }

    return nullptr;
}

//This replaces a victim node if it is clean and hasn't been recently used. Then corresponding data is updatede to reflect the changed state of the circular list.
void PageReplacement::replaceNode(Node* replacementNode){

    Node* currentNode = head;

    //traverses through the list until the node is the appropriate start point for replacement.
    for(int i = 0; i < clockHand; i++){
        currentNode = currentNode->next;
    }

    //Checks to see if current node is either dirty or young enough
    int nodeAge = time - currentNode->lastAccesedTime;
    while(currentNode->isDirty || nodeAge <= ageLimit){
        if(currentNode->isDirty){
            currentNode->isDirty = false;
        }
        currentNode = currentNode->next;
        clockHand++;

        if(clockHand >= maxSize){
            clockHand = 0;
        }

        nodeAge = time - currentNode->lastAccesedTime;
    }

    //replace current node values with the replacement node's values

    currentNode->victimVpn = currentNode->vpn;
    currentNode->vpn = replacementNode->vpn;
    currentNode->isHit = false;
    currentNode->isDirty = actions[time] - '0';

    clockHand++;
    time++;

}