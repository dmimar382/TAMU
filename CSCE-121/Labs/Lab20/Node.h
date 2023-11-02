#ifndef NODE_H
#define NODE_H

struct Node {
    Node() : data(0) {}
    Node(int data) : data(data){}
    int data;
    Node *left = nullptr;
    Node *right = nullptr;
    Node *parent = nullptr;
};


#endif