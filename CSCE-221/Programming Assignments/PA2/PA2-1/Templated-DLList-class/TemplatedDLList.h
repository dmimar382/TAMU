// header file for the templated DLList

#ifndef TEMPLATEDDLLIST_H
#define TEMPLATEDDLLIST_H

#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class DLList; // class declaration

// doubly linked list node
template <typename T>
struct DLListNode {
  T obj;
  DLListNode<T> *prev, *next;
  // constructor
  DLListNode(T e={}, DLListNode *p = nullptr, DLListNode *n = nullptr)
    : obj(e), prev(p), next(n) {}
};

template <typename T>
class DLList {
private:
  DLListNode<T> header, trailer;
public:
  DLList() : header(), trailer() // default constructor
  { header.next = &trailer; trailer.prev = &header; }
  DLList(const DLList& dll); // copy constructor
  DLList(DLList&& dll); // move constructor
  ~DLList(); // destructor
  DLList& operator=(const DLList& dll); // copy assignment operator
  DLList& operator=(DLList&& dll); // move assignment operator
  // return the pointer to the first node
  DLListNode<T> *first_node() const { return header.next; } 
  // return the pointer to the trailer
  const DLListNode<T> *after_last_node() const { return &trailer; }
  // return if the list is empty
  bool is_empty() const { return header.next == &trailer; }
  T first() const; // return the first object
  T last() const; // return the last object
  void insert_first(T obj); // insert to the first node
  T remove_first(); // remove the first node
  void insert_last(T obj); // insert to the last node
  T remove_last(); // remove the last node
  void insert_after(DLListNode<T> &p, T obj);
  void insert_before(DLListNode<T> &p, T obj);
  T remove_after(DLListNode<T> &p);
  T remove_before(DLListNode<T> &p);
};

// output operator
template<typename T>
ostream& operator<<(ostream& out, const DLList<T>& dll);


//this is what I'm adding
struct EmptyDLList : public std::runtime_error {
  explicit EmptyDLList(char const* msg=nullptr): runtime_error(msg) {}
};

template<typename T>
DLList<T>::DLList(const DLList& dll)
{
  //Initialize the list
  header.next = &trailer;
  trailer.prev = &header;

  DLListNode<T> * ptrNode = dll.first_node();
  while(ptrNode != &dll.trailer)
  {
    insert_last(ptrNode->obj);
    ptrNode = ptrNode->next;
  }
}

// move constructor
template<typename T>
DLList<T>::DLList(DLList&& dll)
{
  if(dll.is_empty())
  {
    header.next = &dll.trailer;
    trailer.prev = &dll.header;
  }
  else
  {
	  header.next = dll.header.next;
	  trailer.prev = dll.trailer.prev;
	  dll.header.next->prev = &header;
	  trailer.prev->next = &trailer;
	  dll.header.next = &dll.trailer;
	  dll.trailer.prev = &dll.header;
  }

}

// copy assignment operator
template<typename T>
DLList<T>& DLList<T>::operator=(const DLList& dll)
{
  DLListNode<T> *prev_node = header.next;
  DLListNode<T> *node = header.next;
  while(node != &trailer)
  {
    prev_node = node;
    node = node->next;
    delete prev_node;
  }

  //Initialize the list
  header.next = &trailer;
  trailer.prev = &header;

  DLListNode<T> * ptrNode = dll.first_node();
  while(ptrNode != &dll.trailer)
  {
    insert_last(ptrNode->obj);
    ptrNode = ptrNode->next;
  }

  return *this;
}

// move assignment operator
template<typename T>
DLList<T>& DLList<T>::operator=(DLList&& dll)
{
  if(this != &dll){  
    header.next = dll.header.next;
    trailer.prev = dll.trailer.prev;
    dll.header.next->prev = &header;
    trailer.prev->next = &trailer;
    dll.header.next = &dll.trailer;
    dll.trailer.prev = &dll.header;
  }
  
  return *this;
}

// destructor
template<typename T>
DLList<T>::~DLList()
{
  DLListNode<T> *prev_node = header.next;
  DLListNode<T> *node = header.next;
  while(node != &trailer)
  {
    prev_node = node;
    node = node->next;
    delete prev_node;
  }
  header.next = &trailer;
  trailer.prev = &header;
}

// insert a new object as the first one
template<typename T>
void DLList<T>::insert_first(T obj)
{ 
  DLListNode<T> * newNode = new DLListNode<T>(obj, &header, header.next);
  header.next->prev = newNode;
  header.next = newNode;  
}

// insert a new object as the last one
template<typename T>
void DLList<T>::insert_last(T obj)
{
  DLListNode<T> *newNode = new DLListNode<T>(obj, trailer.prev, &trailer);
  trailer.prev->next = newNode;
  trailer.prev = newNode;
}

// remove the first node from the list
template<typename T>
T DLList<T>::remove_first()
{ 
  if(is_empty())
    throw EmptyDLList("Empty");
  DLListNode<T> *node = header.next;
  node->next->prev = &header;
  header.next= node->next;
  T obj = node->obj;
  delete node;
  return obj; 

}

// remove the last node from the list
template<typename T>
T DLList<T>::remove_last()
{
  if(is_empty())
    throw EmptyDLList("Empty");
  DLListNode<T> *node = trailer.prev;
  node->prev->next = &trailer;
  trailer.prev= node->prev;
  T obj = node->obj;
  delete node;
  return obj;
}

// return the first object (do not remove)
template<typename T>
T DLList<T>::first() const
{ 
  if (is_empty())
    throw EmptyDLList("Empty");
  return header.next-> obj;
}

// return the last object (do not remove)
template<typename T>
T DLList<T>::last() const
{
  if (is_empty())
    throw EmptyDLList("Empty");
  return trailer.prev-> obj;
}

// insert a new node after the node p
template<typename T>
void DLList<T>::insert_after(DLListNode<T> &p, T obj)
{
  DLListNode<T> * newNode = new DLListNode<T>(obj, &p, p.next);
  p.next->prev = newNode;
  p.next = newNode;
}

// insert a new node before the node p
template<typename T>
void DLList<T>::insert_before(DLListNode<T> &p, T obj)
{
  DLListNode<T> * newNode = new DLListNode<T>(obj, p.prev, &p);
  p.prev->next = newNode;
  p.prev = newNode;
}

// remove the node after the node p
template<typename T>
T DLList<T>::remove_after(DLListNode<T> &p)
{
  if(is_empty())
    throw EmptyDLList("Empty");
  if(p.next == &trailer) {
    cout << p.obj <<endl;
    return p.obj;
  }
  DLListNode<T> *node = p.next;
  node->next->prev = &p;
  p.next= node->next;
  T obj = node->obj;
  delete node;
  return obj; 
}

// remove the node before the node p
template<typename T>
T DLList<T>::remove_before(DLListNode<T> &p)
{
  if(is_empty())
    throw EmptyDLList("Empty");
  if(p.prev == &header){
    cout << p.obj <<endl;
    return p.obj;
	}
  DLListNode<T> *node = p.prev;
  node->prev->next = &p;
  p.prev= node->prev;
  T obj = node->obj;
  delete node;
  return obj;
}

template<typename T>
ostream& operator<<(ostream& out, const DLList<T>& dll)
{  
  DLListNode<T> *node = dll.first_node();
  while (node->next != nullptr)
  {
    out << node->obj << " ";
    node = node->next;
  }
  return out;
}



#endif
