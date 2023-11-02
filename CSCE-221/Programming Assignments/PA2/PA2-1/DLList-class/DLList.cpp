// implementation of the DLList class

#include <stdexcept>
#include "DLList.h"

//move constructor with empty list 


// extend runtime_error from <stdexcept>
struct EmptyDLList : public std::runtime_error {
  explicit EmptyDLList(char const* msg=nullptr): runtime_error(msg) {}
};

// copy constructor
DLList::DLList(const DLList& dll)
{
  //Initialize the list
  header.next = &trailer;
  trailer.prev = &header;

  DLListNode * ptrNode = dll.first_node();
  while(ptrNode != &dll.trailer)
  {
    insert_last(ptrNode->obj);
    ptrNode = ptrNode->next;
  }
}

// move constructor
DLList::DLList(DLList&& dll)
{
  if(dll.is_empty())
  {
      //problem with 2 dangling pointers 
    //added this
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
DLList& DLList::operator=(const DLList& dll)
{
  DLListNode *prev_node = header.next;
  DLListNode *node = header.next;
  while(node != &trailer)
  {
    prev_node = node;
    node = node->next;
    delete prev_node;
  }

  //Initialize the list
  header.next = &trailer;
  trailer.prev = &header;

  DLListNode * ptrNode = dll.first_node();
  while(ptrNode != &dll.trailer)
  {
    insert_last(ptrNode->obj);
    ptrNode = ptrNode->next;
  }

  return *this;
}

// move assignment operator
DLList& DLList::operator=(DLList&& dll)
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
DLList::~DLList()
{
  DLListNode *prev_node = header.next;
  DLListNode *node = header.next;
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
void DLList::insert_first(int obj)
{ 
  DLListNode * newNode = new DLListNode(obj, &header, header.next);
  header.next->prev = newNode;
  header.next = newNode;  
}

// insert a new object as the last one
void DLList::insert_last(int obj)
{
  DLListNode *newNode = new DLListNode(obj, trailer.prev, &trailer);
  trailer.prev->next = newNode;
  trailer.prev = newNode;
}

// remove the first node from the list
int DLList::remove_first()
{ 
  if(is_empty())
    throw EmptyDLList("Empty");
  DLListNode *node = header.next;
  node->next->prev = &header;
  header.next= node->next;
  int obj = node->obj;
  delete node;
  return obj; 

}

// remove the last node from the list
int DLList::remove_last()
{
  if(is_empty())
    throw EmptyDLList("Empty");
  DLListNode *node = trailer.prev;
  node->prev->next = &trailer;
  trailer.prev= node->prev;
  int obj = node->obj;
  delete node;
  return obj;
}

// return the first object (do not remove)
int DLList::first() const
{ 
  if (is_empty())
    throw EmptyDLList("Empty");
  return header.next-> obj;
}

// return the last object (do not remove)
int DLList::last() const
{
  if (is_empty())
    throw EmptyDLList("Empty");
  return trailer.prev-> obj;
}

// insert a new node after the node p
void DLList::insert_after(DLListNode &p, int obj)
{
  DLListNode * newNode = new DLListNode(obj, &p, p.next);
  p.next->prev = newNode;
  p.next = newNode;
}

// insert a new node before the node p
void DLList::insert_before(DLListNode &p, int obj)
{
  DLListNode * newNode = new DLListNode(obj, p.prev, &p);
  p.prev->next = newNode;
  p.prev = newNode;
}

// remove the node after the node p
int DLList::remove_after(DLListNode &p)
{
  if(is_empty())
    throw EmptyDLList("Empty");
  if(p.next == &trailer)
    cout << p.obj <<endl;
    return p.obj;
  DLListNode *node = p.next;
  node->next->prev = &p;
  p.next= node->next;
  int obj = node->obj;
  delete node;
  return obj; 
}

// remove the node before the node p
int DLList::remove_before(DLListNode &p)
{
  if(is_empty())
    throw EmptyDLList("Empty");
  if(p.prev == &header)
    cout << p.obj <<endl;
    return p.obj;
  DLListNode *node = p.prev;
  node->prev->next = &p;
  p.prev= node->prev;
  int obj = node->obj;
  delete node;
  return obj;
}

// output operator
ostream& operator<<(ostream& out, const DLList& dll)
{  
  DLListNode *node = dll.first_node();
  while (node->next != nullptr)
  {
    out << node->obj << " ";
    node = node->next;
  }
  return out;
}
