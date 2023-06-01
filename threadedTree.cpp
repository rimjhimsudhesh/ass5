#include "threadedTree.h"
#include <iostream>

using namespace std;

/*
 Iterates through the threadedTree via inorder traversal and prints each node
 
 @param node as the current node to print
 */
void Iterator::inorderTraverse(treeNode *node){
    if (node == nullptr){
        cout << "";
    }

    inorderTraverse(node -> left);
    cout << node -> val << " ";
    inorderTraverse(node -> right);
}

/*
 No parameter constructor for threadedTree class. Creates a nullptr root and does nothing else
 */
threadedTree::threadedTree() : height(0), root(nullptr) {
    root = new treeNode(nullptr, nullptr, nullptr);
}

/*
 Single variable constructor for the threadedTree class
 
 @param n as the largest number in the tree (1 through n)
 */
explicit threadedTree::threadedTree(int n) {
    root = buildTree(1, n);
}

/*
 Copy constructor for threadedTree
 
 @param other as the threadedTree being copied
 */
threadedTree::threadedTree(const threadedTree &other){
    root = copyTreeNode(other.root);
}

/*
 Helper function for copying a threaded tree by recursively creating and copying nodes from original tree
 
 @param node as the treeNode being copied from the original threadedTree
 @return treeNode pointer creating a copied binary tree
 */
treeNode* threadedTree::copyTreeNode(const treeNode* node) {
    if(node == nullptr) {
        return nullptr
    } else {
        treeNode* newNode = new treeNode(node->val);
        newNode->left = copyNode(node->left);
        newNode->right = copyNode(node->right);
        return newNode;
    }
}

/*
 Destructor for threadedTree class
 */
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

/*
 Adds a new node to the threadedTree with a given value
 
 @param val as the value for the new node
 */
void threadedTree::add(int val){
    addHelper(root, val); 
}

/*
 Helper function to add a node to the threadedTree
 
 TODO: Finish this comment section! I don't understand it
 @param node
 @param val
 */
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

/*
 Returns the height of the threadedTree
 
 @return height of the tree
 */
int threadedTree::getHeight(){
    return height;
}

/*
 Returns a boolean value of whether the threadedTree is empty
 
 @return true if threadedTree is empty, false otherwise
 */
bool threadedTree::isEmpty(){
    return root == nullptr;
}
