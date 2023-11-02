#ifndef LinkedList_H
#define LinkedList_H
#include <iostream>
#include <algorithm>
#include <string>
#include "Node.h"

template <typename T> class LinkedList {
public:
    LinkedList();
    LinkedList(std::string);

    LinkedList(const LinkedList<T>&);
    LinkedList(LinkedList<T>&&);
    LinkedList<T>& operator=(const LinkedList<T>&);
    LinkedList<T>& operator=(LinkedList<T>&&);
    ~LinkedList();

    void set_name(std::string);
    std::string get_name() const;
    Node<T>* get_head() const;
    Node<T>* get_tail() const;

    bool is_empty() const;
    void insert_front(int);
    void insert_back(int);
    bool insert_after (int, int);
    void clear();

private:
    Node<T>* head;
    Node<T>* tail;
    std::string name;
    void null_head(bool);
    void null_tail(bool);
    void swap(LinkedList<T>& l1, LinkedList<T> l2);
    void log(const std::string& what) const;
};

template <typename T> inline std::ostream& operator<<(std::ostream& os, const LinkedList<T>& ll)
{
    os << ll.get_name() << " {";
    Node<T>* current = ll.get_head();
    if (current == nullptr) {
        os << " <Empty List>";
    }
    while (current != nullptr) {
        if (current != ll.get_head())
            os << ",";
        os << " " << current->value;
        current = current->next;
    }
    os << " }";
    //os << std::endl << ll.get_head() << '\t' << ll.get_tail() << std::endl;
    return os;
}


using namespace std;

template <typename T>LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr) {}

template <typename T>LinkedList<T>::LinkedList(string name) : head(nullptr), tail(nullptr), name(name) {}
template <typename T>LinkedList<T>::~LinkedList()
{
    this->clear();
}

template <typename T>LinkedList<T>::LinkedList(const LinkedList<T>& source)
{
    Node<T> * source_Node = source.get_head();
    head = new Node<T>(source_Node->value);
    Node<T> * current_Node = head;
    tail = head;
    source_Node = source_Node->next;
    while (source_Node) {
        current_Node->next = new Node<T>(source_Node->value);
        tail = current_Node->next;
        current_Node = current_Node->next;
        source_Node = source_Node->next;
    }
}

template <typename T>LinkedList<T>::LinkedList(LinkedList<T>&& source)
{
    head = source.get_head();
    tail = source.get_tail();
    source.null_head(true);
    source.null_tail(true);
}

template <typename T>LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs)
{
    if (this != &rhs && !rhs.is_empty()) {
        this->swap(*this, rhs); // copy-and-swap idiom
    }
    return *this;
}

template <typename T>LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>&& source)
{
    if (this != &source) {
        Node<T>* next = nullptr;
        clear();
        head = source.get_head();
        tail = source.get_tail();
        source.null_head(true);
        source.null_tail(true);
    }
    return *this;
}

template <typename T>void LinkedList<T>::set_name(string name)
{
    this->name = name;
}

template <typename T>string LinkedList<T>::get_name() const
{
    return name;
}

template <typename T>Node<T>* LinkedList<T>::get_head() const
{
    return head;
}

template <typename T>Node<T>* LinkedList<T>::get_tail() const
{
    return tail;
}

template <typename T>bool LinkedList<T>::is_empty() const
{
    if (head == nullptr && tail == nullptr)
        return true;
    else
        return false;
}

template <typename T>void LinkedList<T>::insert_front(int value)
{
    Node<T>* newNode = new Node<T>(value);
    if (head != nullptr)
        newNode->next = head;
    head = newNode;
    if (tail == nullptr) {
        tail = newNode;
    }
}

template <typename T>void LinkedList<T>::insert_back(int value)
{
    Node<T>* newNode = new Node<T>(value);
    if (tail != nullptr)
        tail->next = newNode;
    tail = newNode;
    if (head == nullptr) {
        head = tail;
    }
}

template <typename T>bool LinkedList<T>::insert_after (int after_val, int insert_val)
{
    if (is_empty())
        return false;
    Node<T> * curr = head;
    while (curr != nullptr) {
        if (curr->value == after_val) {
            Node<T>* new_Node = new Node<T>(insert_val);
            new_Node->next = curr->next;
            curr->next = new_Node;
            if (curr == tail)
                tail = new_Node;
            return true;
        }
        curr = curr->next;
    }
    return false;
}

template <typename T>void LinkedList<T>::clear()
{
    Node<T>* current = head;
    while (current != nullptr) {
        Node<T>* deleteNode = current;
        current = current->next;
        delete deleteNode;
    }
    head = nullptr;
    tail = nullptr;
}

template <typename T>void LinkedList<T>::null_head(bool i_am_sure) { if (i_am_sure) head = nullptr; }
template <typename T>void LinkedList<T>::null_tail(bool i_am_sure) { if (i_am_sure) tail = nullptr; }

template <typename T>void LinkedList<T>::swap(LinkedList<T>& l1, LinkedList<T> l2)
{
    // LinkedList<T> l2 is passed-by-value to this function, so copy constructor creates the object that is put on the stack.
    std::swap(l1.head, l2.head); // swaps l1.head with l2.head
    std::swap(l1.tail, l2.tail); // swaps l1.tail with l2.tail
    // l2's goes out of scope as the function returns, causing l1's original Node<T>s to be deleted (because l2's head now points to l1's orignal head)
}

template <typename T>void LinkedList<T>::log(const string& what) const
{
    std::cout << "[" << this << "] " << what << std::endl;
}


#endif