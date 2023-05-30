#ifndef TREENODE.H
#define TREENODE.H
#include <iostream>

using namespace std;

class treeNode {
    friend ostream& operator<<(ostream& out, const treeNode &Node);
    
    public:
        // Constructor for the treeNode object
        treeNode(int value, treeNode* left, treeNode* right);
        // Returns true if the treeNode is a leaf, false if it has children
        bool isLeaf(); 
    private:
        // Pointer to the left child OR to a parent is isLeaf() is true
        treeNode* left;
        // Pointer to the right child OR to a parent if isLeaf() is true
        treeNode* right;
        // True if the treeNode is a leaf AND is not the final leaf in the tree
        bool threaded;
        // Has the value of the node 
        int val;
        
    
};
#endif