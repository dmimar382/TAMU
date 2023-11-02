#include "BasicTree.h"
#include "Node.h"
#include <queue>
#include <cstdio>
using namespace std;

class val_not_found{};

BasicTree::BasicTree() : root{nullptr} {}
BasicTree::BasicTree(int i) : root{new Node(i)} {}
BasicTree::~BasicTree(){
    delete_tree(root);
}

void BasicTree::delete_tree(Node *n)
{
    if(!n){
        return;
    }
    delete_tree(n->left); 
    // 2. Traverse the left subtree by visiting node to the left of the current node.
    delete_tree(n->right);
    delete n;
}
Node* BasicTree::get_root(){
    return root;
}

void BasicTree::insert(int val)
{
    rec_insert(root, val);
} 
void BasicTree::rec_insert(Node* curr, int val) {
    //Node* n = new Node(val);
    // 1. Check whether the tree is empty or not;
    if (root == nullptr) {
        root = new Node(val); // 2a. if the tree is empty set root equal to a new node with the passed value and return.
        return;   
    }
    // 2b. Otherwise, find the proper location to tag on a new node storing the passed value on to the tree; be sure to set this node's Node* parent to the node preceding it in the tree.
    if (curr->data > val){ 
        if (curr->left == nullptr) {
            curr->left = new Node(val);; 
            return;
        }
        rec_insert(curr->left, val); 
    }
    if (curr->data < val){
        if (curr->right == nullptr) {
            curr->right = new Node(val);; 
            return;
        }
        rec_insert(curr->right, val);
    }
}

ostream& BasicTree::in_order(Node *curr, ostream &os)
{
    if (!curr)
        return os; 
        // 1. Traverse the left subtree by visiting node to the left of the current node.
    in_order(curr->left, os); 
   // 2. Visit the current node; insert its value to the stream.
    os << curr->data << " "; 
    // 3. Traverse the right subtree by visiting node to the right of the current node.
    in_order(curr->right, os);
    // 4. Return the stream
}

ostream& BasicTree::post_order(Node *n, ostream &os)
{
    // 1. Traverse the left subtree by visiting node to the left of the current node.
    if (!n) 
        return os; 
    post_order(n->left, os); 
    post_order(n->right, os); 
    os << n->data << " ";
    // 2. Traverse the right subtree by visiting the node to the right of the current node.

    // 3. Visit the current node; insert its value to the stream.

    // 4. Return the stream
    return os;
}

ostream& BasicTree::pre_order(Node *n, ostream &os)
{
    if (!n) 
        return os;
    os << n->data << " "; 
    // 1. Visit the current node; insert its value to the stream.
    pre_order(n->left, os); 
    // 2. Traverse the left subtree by visiting node to the left of the current node.
    pre_order(n->right, os);
    // 3. Traverse the right subtree by visiting the node to the right of the current node.

    // 4. Return the stream
    return os;
}

int const& BasicTree::find(int val) { 
     return rec_find(val,root)->data; 
}
Node* BasicTree::rec_find(int val, Node* curr) {
    if (!curr) {
        throw val_not_found{};   
    }
    if (curr->data > val){ 
        return rec_find(val, curr->left); 
    }
    if (curr->data < val) {
        return rec_find(val, curr->right); 
    }
    return curr; 
}

///////////////////////////////////////////////////////////////////////////////
// operator<< support
///////////////////////////////////////////////////////////////////////////////
stringstream& BasicTree::to_sstream(Node *n, int depth, string s, stringstream& os) const
{
    if (n==nullptr) {
        os << "Empty" << endl;
        return os;
    }
    os << "("<<n->data<<") Address: " << n << " Parent: " << n->parent << "\n";
    os << s << " `--[L]";
    s += " |  ";
    if (n->left)
        to_sstream(n->left, depth + 1, s, os);
    else
        os <<"nullptr\n";
    s.erase(s.end() - 4, s.end());

    os << s << " `--[R]";
    s += "    ";
    if (n->right)
        to_sstream(n->right, depth + 1, s, os);
    else
        os <<"nullptr\n";
    s.erase(s.end() - 4, s.end());
    return os;
}

ostream& operator<<(ostream& os, BasicTree const& bt)
{
    os << bt.to_str();
    return os;
}


BasicTree::BasicTree(BasicTree const& copy)
{
    root = nullptr;
    copytree(copy.root);
}

void BasicTree::copytree(Node* n)
{
    if (!n) 
        return;
    insert(n->data);
    // 1. Visit the current node; insert its value to the stream.
    copytree(n->left); 
    // 2. Traverse the left subtree by visiting node to the left of the current node.
    copytree(n->right);
    // 3. Traverse the right subtree by visiting the node to the right of the current node.

    // 4. Return the stream

}
BasicTree& BasicTree::operator=(BasicTree const& bt){
    if (root == bt.root)
        return *bt;

    delete_tree(root);
    copytree(bt.root);
}
