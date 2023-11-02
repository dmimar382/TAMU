#include <iostream>
# include <vector>
using namespace std; //Blank A
class node {
 public://Blank B	
 	int val;
 	node* next;
};
 
void create_LL(vector<node*>& mylist, int node_num){
    mylist.assign(node_num, NULL);

    //create a set of nodes
    for (int i = 0; i < node_num; i++) {
        mylist[i] = new node;//Blank C
        mylist[i]->val = i;
        mylist[i]->next = NULL;
    }

    //create a linked list
    for (int i = 0; i < node_num-1; i++) {
        mylist[i]->next = mylist[i+1];
    }
}

int sum_LL(node* ptr) {
    int ret = 0;
    while(ptr) {
        ret += ptr->val;
        ptr = ptr->next;
    }
    return ret;
}

int main(int argc, char ** argv){
    const int NODE_NUM = 3;
    vector<node*> mylist;

    create_LL(mylist, NODE_NUM);
    int ret = sum_LL(mylist[0]); 
    cout << "The sum of nodes in LL is " << ret << endl;

    //Step4: delete nodes
    for (int i = 0; i < NODE_NUM; i++) {
        delete mylist[i];
	mylist[i] = nullptr;

    }
    //Blank D
}