#ifndef THREADEDTREE.H
#define THREADEDTREE.H
#include <iostream>

using namespace std;

class threadedTree{
    friend class treeNode;
    public:
        // Cons
        threadedTree(int n);
        // Copy Constructor
        threadedTree(const threadedTree &other);
        // destructor
        ~threadedTree();
    private:
        // return true if successfully removed
        bool remove(int val);
        // return true if found in tree
        bool contains(int val) const;
        // add to tree
        void add(int val);

};

#endif