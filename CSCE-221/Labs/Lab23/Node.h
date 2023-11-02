#ifndef NODE_H
#define NODE_H
#include <iostream>

template <typename T> struct Node
{
    T value;
    Node<T>* next;
    Node(T value) : value(value), next(nullptr) {}
    Node() : value(0), next(nullptr) {}
};

template <typename T> inline std::ostream& operator<<(std::ostream& os, const Node<T>& n)
{
    os << n.value;
    return os;
}

#endif