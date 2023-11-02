#ifndef NODE_H
#define NODE_H

struct Node {
    Node() : data(0), next(nullptr), prev(nullptr) {}
    Node(int data) : data(data), next(nullptr), prev(nullptr) {}
    int data;
    Node* next;
    Node* prev;
};

#endif