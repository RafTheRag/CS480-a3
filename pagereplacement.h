#ifndef PAGEREPLACEMENT_H
#define PAGEREPLACEMENT_H

class Node{
    public:
        Node* next = nullptr;
        int vpn;
        int lastAccesedTime;
        bool isDirty = false;

        Node(int vpn, int access);
};

class PageReplacement{
    public:
        Node* head;
        int clockHand = 0;
        int maxSize;
        int time = 0;
        bool isFull = false;

        PageReplacement(int maxSize);
        void insertNode(Node* node);
        void replaceNode(Node* node);
};




#endif