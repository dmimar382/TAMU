#ifndef BASICTREE_H
#define BASICTREE_H
#include "Node.h"
#include <iostream>
#include <string>
#include <sstream>

class BasicTree {
public:
    BasicTree();
    ~BasicTree();
    BasicTree(int);
    // BasicTree~();
    BasicTree(BasicTree const&); // C++11 means of explicitly disabling copy constructor
    BasicTree& operator=(BasicTree const&); // C++11 means of explicitly disabling copy assignment operator
    void insert(int);
    void rec_insert(Node*, int);
    void delete_tree(Node*);
    Node* get_root();
    int const& find(int);
    Node* rec_find(int, Node*);
    void copytree(Node*);

    // Traversals : Wrappers
    std::ostream& in_order(std::ostream& os = std::cout) {return in_order(root, os) << std::endl;}
    std::ostream& post_order(std::ostream& os = std::cout) {return post_order(root, os) << std::endl;}
    std::ostream& pre_order(std::ostream& os = std::cout) {return pre_order(root, os) << std::endl;}

    // operator<< support
    std::string to_str() const {std::stringstream ss; return (to_sstream(root, 0, "", ss)).str();}
private:
    Node* root;

    // Traversals : Actual
    std::ostream& in_order(Node*, std::ostream&);
    std::ostream& post_order(Node*, std::ostream&);
    std::ostream& pre_order(Node*, std::ostream&);

    // operator<< support
    std::stringstream& to_sstream(Node*, int, std::string, std::stringstream&) const;
};

std::ostream& operator<<(std::ostream&, BasicTree const&);

#endif