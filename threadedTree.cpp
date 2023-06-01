#include "threadedTree.h"
#include <iostream>

using namespace std;

void Iterator::inorderTraverse(treeNode *node){
    if (node == nullptr){
        cout << "";
    }

    inorderTraverse(node -> left);
    cout << node -> val << " ";
    inorderTraverse(node -> right);
}

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

/*
 Builds a tree given a start (1) and end (input) recursively through a binary method
 
 @param start as smallest integer
 @param end as largest integer
 @return treeNode pointer for children and root
 */
treeNode* buildTree(int start, int end) {
    if(start > end) {
        return nullptr;
    } else {
        int mid = end/2;
        treeNode* root = new TreeNode();
        root->value = mid;
        root->right = buildTree(mid + 1, end);
        root->left = buildTree(start, mid - 1);
        return root;
    }
}

/*
 Deletes all nodes from the tree
 
 @param node as the current node being cleared
 */
void threadedTree::clear(treeNode* node){
    if(node != nullptr){
        clear(node -> left);

        if(root -> threaded){
            clear(node -> right);
        }
    }

    delete root;

}

/*
 Checks the tree to find if a value is in the tree
 
 @param val as the value being searched for
 @return true if the value is present, false otherwise
 */
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
    addHelper(root, val); 
}

void threadedTree::addHelper(treeNode *node, int val){
    treeNode* par = nullptr;
    treeNode* ptr = root;


    while(ptr != null){
        par = ptr;

        if(val < ptr -> val){
            if(ptr -> threaded == false){
                ptr = ptr -> left;
            }

            else{
                break;
            }
        }

        else{
            if(ptr -> threaded == false){
                ptr = ptr -> right;
            }

            else{
                break;
            }
        }

        treeNode *tmp = new treeNode;
        tmp -> val = val;
        tmp -> threaded = true;

        if(par == null){
            root = tmp;
            temp -> left = nullptr;
            temp -> right = nullptr;
        }

        else if(val < par -> val){
            tmp -> left = par -> left;
            tmp -> right = par;
            par -> threaded = false;
            par -> left = tmp;
        }

        else{
            tmp -> left = par;
            tmp -> right = par -> right;
            par -> threaded = false;
            par -> right = tmp;
        }

    }
    
    

}

/*
 Remove method to satisfy the precondition of removeHelper
 
 @param val as the value being removed/searched for in the tree
 @return true if present and removed, false otherwise
 */
bool threadedTree::remove(const int val) {
    if(!contains(val)) {
        return false;
    } else {
        removeHelper(root, val);
        return true;
    }
}

/*
  Precondition: Node is in tree
  Recursively finds a node in a tree and deletes it from the tree
  
  @param node as the current node in tree
  @param val as the value being searched for
  @return treeNode pointer to replace deleted node
  */
treeNode* threadedTree::removeHelper(treeNode* node, int val){
    if(val < node->val) {
        node->left = removeHelper(node->left, val);
    } else if(val > node->val) {
        node->right = removeHelper(node->right, val);
    } else {
        if(node->left == nullptr) {
            treeNode* temp = node->right;
            delete node;
            return temp;
        } else if(node->right == nullptr) {
            treeNode* temp = node->left;
            delete node;
            return temp;
        } else {
            treeNode* temp = smallestNode(node->right);
            node->val = temp->val;
            removeHelper(node->right, temp->val);
        }
    }
    return node;
}

/*
 This function returns the smallest node from a branch
 
 @param node as the branch to be searched
 @return treeNode pointer to the smallest treeNode in the branch
 */
treeNode* smallestNode(treeNode* node) {
    treeNode* cur = node;
    while(cur->left != nullptr) {
        cur = cur->left;
    }
    return cur;
}


int threadedTree::getHeight(){
    return height;
}

bool threadedTree::isEmpty(){
    return root == nullptr;
}


