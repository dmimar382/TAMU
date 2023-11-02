
#include "BSTree.h"
#include <iostream>

// input / output operators
ostream& operator<<(ostream& out, BSTree& tree)
{
  //cout << "output operator" <<endl;
  tree.print_level_by_level(out);
  return out;
}

ostream& operator<<(ostream& out, Node node)
{
  return out << "( " << node.value << ", "
	     << node.search_time << " )";
}

istream& operator>>(istream& in, BSTree& tree)
{
  /*
    take input from the in stream, and build your tree
    input will look like
    4 
    2 
    6 
    1 
    3 
    5 
    7
  */
  int next;
  while(in >> next) 
    tree.insert(next);
  return in;
}

///////////// Implementation To Do ////////////////////

// copy constructor
BSTree::BSTree(const BSTree& other)
{
  /*
    complete this copy constructor
    make sure when copying nodes to copy
    the value and left and right children
  */
  if(other.root == nullptr)
  {
    this->root = nullptr;
    this->size = 0;
  }
  else
  {
    this->root = nullptr;
    this->root = new Node(other.root->value);
    this->root->search_time = other.root->search_time;
    copy_helper(this->root, other.root);
    this->size = other.size;
  }
}

// move constructor
BSTree::BSTree(BSTree&& other)
{
  this->root = other.root;
  this->size = other.size;
  other.root = nullptr;
  other.size = 0;
}

//copy assignment
BSTree& BSTree::operator=(const BSTree& other)
{
  /*
    complete this assignment operator
    make sure when copying nodes to copy
    the value
    and left and right children
    not important for this part but will be used later
  */
  if(this->root == other.root)
    return *this;

  if(other.root==nullptr)
  {
    delete_tree(this->root);
  }
  else if(this->root != other.root)
  {
    delete_tree(this->root);
    this->root = new Node(other.root->value);
    this->root->search_time = other.root->search_time;
    copy_helper(this->root, other.root);
    this->size = other.size;
  }

  return *this;
}

// move assignment
BSTree& BSTree::operator=(BSTree&& other)
{
  //check for self assignemnt 
  // if (this->root == other.root)
  // {
  //   cout << "Self assignemnt" <<endl;
  //   return *this;

  // }
  // if (other.root == nullptr)
  // {
  //   cout << "Nothing to assign" <<endl;
  // }
  if(this->root == other.root)
    return *this;

  if(other.root==nullptr)
  {
    delete_tree(this->root);
  }

  if(other.root != nullptr)
  {
    delete_tree(this->root);
    this->root = other.root;
    this->size = other.size;
    //this->root->search_time = other.root->search_time;
    other.root = nullptr;
    other.size = 0; 
  }
  return *this;
}

// destructor
BSTree::~BSTree()
{ 
  delete_tree(root);// use a helper function

}

void BSTree::delete_tree(Node* r)
{

  if(r == nullptr)
  {
    return;
    //cout << "Null" <<endl;
  }
  if (r->left != nullptr)
  {
    delete_tree(r->left);
  }
  if(r->right != nullptr)
  {
    delete_tree(r->right);
  }
  delete r;

  if (r == root)
  {
    root = nullptr;
    size = 0;
  }
}

// recursive
void BSTree::copy_helper(Node* copy_to,
			 const Node* copy_from) const
{
  if(copy_from == nullptr)
  {
    cout <<"Nothing in copy from" <<endl;
    return;
  }

  if(copy_from->left != nullptr) {
    copy_to->left = new Node(*copy_from->left);
    copy_helper(copy_to->left, copy_from->left);
  } else {
    copy_to->left = nullptr;
  }

  if(copy_from->right != nullptr) {
    copy_to->right = new Node(*copy_from->right);
    copy_helper(copy_to->right, copy_from->right);
  } else {
    copy_to->right = nullptr;
  }
}


Node* BSTree::insert(int obj)
{  
  //   insert a node into the tree
  //   first find where the node should go
  //   then modify pointers to connect your new node
  Node * temp = insert_helper(obj, root);
  size++;
  update_search_times();
  return temp;
}

//what to do with same number being inserted 
Node* BSTree::insert_helper(int obj, Node* r)
{
  //cout << "Num comparisons" << num_comparisons << endl;
  if(root == nullptr)
    root = new Node(obj);

  else if(r == nullptr)
    r = new Node(obj);

  else if(obj <= r->value)
    r->left = insert_helper(obj, r->left);

  else if(obj > r->value)
    r->right = insert_helper(obj, r->right);

  else
    ; //Duplicate, do nothing

  return r;
}


Node* BSTree::search(int obj)
{
  /*
    recursivly search down the tree to find the node that contains obj
    if you dont find anything return null
  */
  return search_helper(obj, root);
}

Node* BSTree::search_helper(int obj, Node* r)
{
  if (root == nullptr)
  {
    cout << "Tree is empty" <<endl;
    return nullptr;
  }
   else if(r == nullptr)
  {
    cout << obj << " not found" <<endl;
    return nullptr;
  }
  else if(obj < r->value)
  {
    search_helper(obj, r->left);
  }
  else if(obj > r->value)
  {
    search_helper(obj, r->right);
  }
  else
  {
    cout <<"Value " <<obj << " found" <<endl;
    return r;
  }
}

void BSTree::update_search_times()
{
  /*
    do a BFS or DFS of your tree and update the searchtimes of all nodes
  */
  int num_comparisons = 0;
  update_search_times_helper(root, num_comparisons);
}

void BSTree::update_search_times_helper(Node* r, int num_comparisons)
{
  
  num_comparisons++;
  if (r != nullptr)
  {
    update_search_times_helper(r->left, num_comparisons);
    //cout << "Out of left" <<endl;
    r->search_time = num_comparisons;
    update_search_times_helper(r->right, num_comparisons);
    //cout << "out of right" <<endl;
  }
}


ostream& BSTree::inorder(ostream& out)
{
  /*
    print your nodes in infix order
    if our tree looks like 

    4
    2 6
    1 3 5 7

    we should get

    1 2 3 4 5 6 7 
  */
  inorder_helper(root, out);
  return out;
}


ostream& BSTree::inorder_helper(Node* r, ostream& out )
{
  // if (r == nullptr)
  //   out << "Nothing in the tree " <<endl;
  if (r != nullptr)
  {
    inorder_helper(r->left, out);
    //cout << "Out of left" <<endl;
    out << r->value  << "[" <<r->search_time << "] ";;
    inorder_helper(r->right, out);
    //cout << "out of right" <<endl;
  }

  //cout << "Returning " << out << endl;
  return out;
}




/////////////////////////////////////////////////////////////////////////////////////

// implemented
void BSTree::pretty_print_node(ostream& out , Node* node)
{
  out << node->value << "["<<node->search_time<<"] ";
}

// implemented
ostream& BSTree::print_level_by_level(ostream& out)
{
  /*
    print the tree using a BFS 
    output should look like this if we dont have a full tree

    4
    2 6
    1 X 5 7
    X X X X X X X 9

    it will be helpfull to do this part iterativly, 
    so do the BFS with the std stack data structure.

    it may also be helpfull to put the entire tree into a vector 
    (probably google this if you dont know how to do it)
  */
  //cout <<"Level by level:" <<endl;
  if(root == nullptr)
  {
    cout <<"empty tree in print" <<endl;
    return out;
  }

  bool hasNodes = true;
  vector<Node*> current_level;
  vector<Node*> next_level;
  current_level.push_back(root);
  while(hasNodes) {
    hasNodes = false;
    for(auto node : current_level) {
      if(node != nullptr) {
	pretty_print_node(out, node);
	if(node->left != nullptr)
	  hasNodes = true;
	if(node->right != nullptr)
	  hasNodes = true;
	
	next_level.push_back(node->left);
	next_level.push_back(node->right);
      } else {
	out << "X ";
	next_level.push_back(nullptr);
	next_level.push_back(nullptr);
      }
    }
    out << endl;
    current_level.clear();
    current_level = next_level;
    next_level.clear();
  }

  return out;
}

// implemented
int BSTree::get_total_search_time(Node* node)
{
  if(node == nullptr)
    return 0;

  return get_total_search_time(node->left) +
    get_total_search_time(node->right) + node->search_time;
}

// implemented
float BSTree::get_average_search_time()
{
  int total_search_time = get_total_search_time(root);
  // cout << "Total search time: " << total_search_time <<endl;
  // cout << "Size:" << size << endl ;
  if(total_search_time == 0)
    return -1;
	
  return ((float)total_search_time)/size;
}


