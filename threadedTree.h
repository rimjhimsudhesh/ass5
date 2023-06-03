#ifndef THREADEDTREE_H
#define THREADEDTREE_H
#include <iostream>

using namespace std;

class threadedTree;

class treeNode {
    friend ostream& operator<<(ostream& out, const treeNode &Node);
    friend class threadedTree;
    friend class Iterator;
    
    public:
        treeNode();
        // Constructor for the treeNode object
        treeNode(int value, treeNode* left, treeNode* right);
        // Returns true if the treeNode is a leaf, false if it has children
        bool isLeaf(const treeNode* node); 
    private:
        // Pointer to the left child OR to a parent is isLeaf() is true
        treeNode* left;
        // Pointer to the right child OR to a parent if isLeaf() is true
        treeNode* right;
        // Pointer to the inorder successor
        treeNode* rightThread;
        // Pointer to the inorder predecessor
        treeNode* leftThread;
        // True if the treeNode is a leaf AND is not the final leaf in the tree
        bool threaded;
        // Has the value of the node 
        int val;
};

class threadedTree{
    // Outputs an entire threadedTree
    friend class treeNode;
    friend class Iterator;
    friend ostream& operator<<(ostream& out, const threadedTree& tree);
    public:
        treeNode* root;
        // Constructor
        threadedTree();
        explicit threadedTree(int n);
        // Copy Constructor
        threadedTree(const threadedTree &other);
        // destructor
        virtual ~threadedTree();
        // return true if successfully removed
        bool remove(int val);
        // return true if found in tree
        bool contains(int val) const;
        // add to tree
        void add(int val);
        // Returns true if empty, false if not
        bool isEmpty();
        // Returns the height of the tree
        int getHeight();
        // Returns true if there is a threaded connection to the in-order successor
        treeNode* threadNodes(treeNode *node);
        
        void inorderTraverse(const threadedTree& tree); // add a parameter for tree node
        
        void inorderHelper(treeNode* node);

    private:
        // Contains the height of the tree
        int height;
        // Pointer to the root of the tree
       
        // Removes all treeNodes from the threadedTree
        void clear(treeNode* node);
        // Takes the current treeNode and creates a thread to the next largest value
        treeNode* nextThread(const treeNode* current);

        treeNode* copyTreeNode(const treeNode* node);

        treeNode* addHelper(treeNode* node, int val);

        treeNode* removeHelper(treeNode *node, int val);

        treeNode* buildTree(int start, int end);

        treeNode* smallestNode(treeNode* node);

        void threadLeft( treeNode* node);

        void rethread(const treeNode* argNode);

        void threadRight( treeNode* argNode);

        treeNode* findParent(int val);
};

#endif
