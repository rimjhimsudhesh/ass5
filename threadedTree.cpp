#include "threadedTree.h"

threadedTree::threadedTree(int n) : height(0), root(nullptr) {
    root = new treeNode(n, nullptr, nullptr);
}

// unsure about how to go about this, if you have any idea how to implement this pls feel free to do so
threadedTree::threadedTree(const threadedTree &other){
    //root = new treeNode(other.val, nullptr, nullptr);

}

threadedTree::~threadedTree(){
    clear(root);
}

void threadedTree::clear(treeNode* node){
    if(node != nullptr){
        clear(node -> left);

        if(root -> threaded){
            clear(node -> right);
        }
    }

    delete root;

}

// i think this is right bc it's a mix of from chatgpt plus my own work
bool threadedTree::contains(int val) const{
    treeNode* current = root;
    while(current != nullptr){
        if(current-> val == val){
            return true;
        }

        if(val < current -> val){
            if(!current -> isLeaf()){
                current = current -> left;
            } 
            
            else{
                break;
            } 
        }

        else{
            if(current -> threaded){
                current = current -> right;
            }
            else{
                current = current -> right;
                while(current != nullptr){
                    current = current -> left;
                }
            }

        }
    }


    return false;
}

void threadedTree::add(int val){
    // i plan to start this 
}

bool threadedTree::remove(int val){
    // feel free to implement this method
}

int threadedTree::getHeight(){
    return height;
}

bool threadedTree::isEmpty(){
    return root == nullptr;
}


