#include "pagereplacement.h"

Node::Node(int vpn, int access) : vpn(vpn), lastAccesedTime(access){}

PageReplacement::PageReplacement(int maxSize) : maxSize(maxSize){

    Node* head;

}

void PageReplacement::insertNode(Node* node){

    Node* currentNode = head;

    if(isFull && !node->isDirty){
        
        replaceNode(node);
    }

    
    if(clockHand >= maxSize){
        clockHand = 0;
        isFull = true;
        node->next = head;
    }

    for(int i = 0; i < clockHand; i++){
        if(currentNode->next == nullptr){
            currentNode->next = node;
            break;
        }
        currentNode = currentNode->next;
    }

}

void PageReplacement::replaceNode(Node* node){

}