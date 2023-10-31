#include "pagereplacement.h"
#include <fstream>
#include <iostream>

Node::Node(int vpn) : vpn(vpn){}

PageReplacement::PageReplacement(int maxSize, int ageLimit, std::string readWriteFile) : maxSize(maxSize), ageLimit(ageLimit), readWriteFile(readWriteFile){

    std::fstream file(readWriteFile);
    file.seekg(0, std::ios::end);
    std::streampos fileSize = file.tellg();
    file.seekg(0, std::ios::beg);
    
    actions = new char[fileSize];

    file.read(actions, fileSize);
    file.close();
    
}

void PageReplacement::insertNode(Node* node){

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

    while(currentNode->next){
        currentNode = currentNode->next;
    }
    node->lastAccesedTime = time;
    node->frame = clockHand;
    if(!node->isDirty && (actions[time] - '0')) node->isDirty = true;
    currentNode->next = node;
    clockHand++;
    time++;

    if(clockHand >= maxSize){
        isFull = true;
        node->next = head;
        clockHand = 0;
    }
}

bool PageReplacement::nodeExists(Node* node){
    
    Node* currentNode = head;

    while(currentNode != nullptr && currentNode->next != head){

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

void PageReplacement::replaceNode(Node* replacementNode){

    Node* currentNode = head;

    for(int i = 0; i < clockHand; i++){
        currentNode = currentNode->next;
    }

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
    
    currentNode->victimVpn = currentNode->vpn;
    currentNode->vpn = replacementNode->vpn;
    currentNode->isHit = false;
    currentNode->isDirty = actions[time] - '0';

    clockHand++;
    time++;
    
}