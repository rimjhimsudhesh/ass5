#include "threadedTree.h"
#include <iostream>
#include <stack>

using namespace std;

// Rimjhim Sudhesh and Michael Schwartz
// 🐇🐇🐇


/*
    Constructor for a treeNode object

    @param value as the value to assign to the treeNode
    @param left as the address to be assigned to left
    @param right as the address to be assigned to right
*/
treeNode::treeNode(int value, treeNode* left, treeNode* right) : val(value), left(left), right(right) {
    this -> threaded = true;
}

treeNode::treeNode() {
}

/*
 Iterates through the threadedTree via inorder traversal and prints each node
 
 @param node as the current node to print
 */
void threadedTree::inorderTraverse() {
    if(root == nullptr) {
        cout << "Tree is empty!" << endl;
        return;
    }
    inorderHelper(root);
}

/*
    Helper function for inorderTraverse to output the correct values

    @param node as the node currently being output
*/
void threadedTree::inorderHelper(treeNode* node) {
    if (node == nullptr) {
        return;
    }

    inorderHelper(node->left);
    cout << node->val << " ";
    inorderHelper(node->right); 

    
}


/*
 No parameter constructor for threadedTree class. Creates a nullptr root and does nothing else
 */
threadedTree::threadedTree() : height(0), root(nullptr) {
    root = new treeNode(0, nullptr, nullptr);
}

/*
 Single variable constructor for the threadedTree class
 
 @param n as the largest number in the tree (1 through n)
 */
threadedTree::threadedTree(int n) {
    root = buildTree(1, n);
    threadNodes(root);
}

/*
    Threads all nodes in the tree together

    @param inputNode as the beginning node to start threading
*/
void threadedTree::threadNodes(treeNode *inputNode){
    treeNode *currentNode;
    currentNode = inputNode;
    treeNode *smallestValue = smallestNode(root);
    //cout << "root is " << root -> val << endl;
    //cout << "starting left side" << endl;
    //cout << "currentNode " << currentNode -> val << endl;
    //cout << "inputNode " << inputNode -> val << endl;
    treeNode *largestValue = rightMost(root);
    if(currentNode -> left != nullptr){
        //cout << "going left" << endl;
        threadNodes(currentNode -> left);
    }

    else if(currentNode -> left == nullptr){
        //cout << "found place to thread" << endl;
        if(currentNode != smallestValue){
            //cout << "threading left..." << endl;
            currentNode -> leftThread = inorderPredecessor(currentNode);
            //cout << "left thread value " << currentNode -> leftThread -> val << endl;
        }
    }

    currentNode = inputNode;
    //cout << "starting right side" << endl;
    //cout << "currentNode " << currentNode -> val << endl;
    //cout << "inputNode " << inputNode -> val << endl;

    if(currentNode -> right != nullptr){
       // cout << "going right" << endl;
        threadNodes(currentNode -> right);
    }
    else if(currentNode -> right == nullptr){
        //cout << "found place to thread" << endl;
        if(currentNode != largestValue){
        //cout << "threading right..." << endl;
           currentNode -> rightThread = inorderSuccessor(currentNode, root);
           //cout << "right thread value " << currentNode -> rightThread -> val << endl;
        }
    }
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
        return nullptr;
    } 
    else {
        treeNode* newNode = new treeNode(node->val, nullptr, nullptr);
        newNode->left = copyTreeNode(node->left);
        newNode->right = copyTreeNode(node->right);
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
treeNode* threadedTree::buildTree(int start, int end) {
    if(start > end) {
        return nullptr;
    } else {
        int mid = (start + end) / 2;
        treeNode* root = new treeNode(mid, nullptr, nullptr);
        root->left = buildTree(start, mid - 1);
        root->right = buildTree(mid + 1, end);
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
    delete node;

}

/*
 Checks the tree to find if a value is in the tree
 
 @param val as the value being searched for
 @return true if the value is present, false otherwise
 */
bool threadedTree::contains(int val) const {
    treeNode* current = root;
    while (current != nullptr) {
        if (current->val == val) {
            return true;
        }

        if (val < current->val) {
            if (!current->leftThread) {
                current = current->left;
            } else {
                break;
            }
        } else {
            if (current->rightThread) {
                current = current->right;
            } else {
                current = current->right;
                if (current != nullptr) {
                    while (current->left != nullptr) {
                        current = current->left;
                    }
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
 
 @param node as node being passed
 @param val as the value of the added treeNode
 @return treeNode pointer to new node
 */
treeNode* threadedTree::addHelper(treeNode* node, int val) {
    if (node == nullptr) {
        treeNode* newNode = new treeNode(val, nullptr, nullptr);
        node = newNode;
        return node;
    }
        
        if(val < node -> val){
            if(node->left == nullptr) {
                node->left = addHelper(node->left, val);
                treeNode* temp = node->leftThread;
                node->leftThread = node->left;
                node->leftThread->rightThread = node;
                node->leftThread->leftThread = temp;
            } else {
                node -> left = addHelper(node -> left, val);
            }
        } else if(val > node -> val){
            if(node -> right == nullptr) {
                node->right = addHelper(node->right, val);
                treeNode* temp = node->rightThread;
                node->rightThread = node->right;
                node->rightThread->leftThread = node;
                node->rightThread->rightThread = temp;
            } else {
                node -> right = addHelper(node -> right, val);
            }
        } else{
            treeNode* newNode = new treeNode(val, nullptr, nullptr);
            node -> rightThread -> leftThread = node -> leftThread;
            newNode -> rightThread = node -> rightThread;
            node -> leftThread -> rightThread = node -> rightThread;
            newNode -> leftThread = node;
            if(node -> left == nullptr){
                treeNode *temp = node -> right;
                delete node;
                return temp;
            } else if(node -> right == nullptr){
                treeNode *temp = node -> left;
                delete node;
                return temp;
            }  else{
                treeNode *temp = smallestNode(node -> right);
                node -> val = temp -> val;
                node -> right = addHelper(node -> right, temp -> val);

            }
        } 
        return node; 
    
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
        cout << "traverse in the remove method: ";
        inorderTraverse();
        return true;
    }
}

/*
  Precondition: Node is in tree
  Recursively finds a node in a tree and deletes it from the tree
  
  @param node as the current node in tree
  @param val as the value being searched for
  @return treeNode pointer to replace   deleted node
  */
treeNode* threadedTree::removeHelper(treeNode* root, int val){

    treeNode* node = root;

    if(val < node->val) {
        node->left = removeHelper(node->left, val);
    } else if(val > node->val) {
        node->right = removeHelper(node->right, val);
    }else{
        cout << "found node: " << node -> val << endl;
        inorderTraverse();
        cout << endl;
        if(node -> right != nullptr){
            //treeNode *parent = findParent(node -> val);
            inorderTraverse();
            cout << endl;
            node -> leftThread -> right = node -> right;
            cout << "node -> leftThread -> right: " << node -> leftThread -> right -> val << endl;
            inorderTraverse(); 
            cout << endl;
            node -> right -> leftThread = node -> leftThread;
            cout << "node -> right -> leftThread: " << node -> right -> leftThread -> val << endl;
            inorderTraverse();
            cout << endl;
            return node->right;
        }
    }

    return nullptr;
    
}


/*
 This function returns the smallest node from a branch
 
 @param node as the branch to be searched
 @return treeNode pointer to the smallest treeNode in the branch
 */
treeNode* threadedTree::smallestNode(treeNode* node) {
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

/*
    Creates a thread to the node on the left for a given node

    @param node as the node being threaded
*/
void threadedTree::threadLeft( treeNode* node) {
    int desired = node->val - 1;
    treeNode* cur = root;
    while(cur->val != desired) {
        if(desired < cur->val) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
        
    }
    node->leftThread = cur;
    
}

/*
    Creates a thread to the node on the right for a given node

    @param node as the node being threaded
*/
void threadedTree::threadRight(treeNode* node) {
    int desired = node->val + 1;
    treeNode* cur = root;
    while(cur->val != desired) {
        if(desired < cur->val) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
         
    }
    node->rightThread = cur;
}

treeNode* threadedTree:: minValueNode(treeNode* node) {
    treeNode* current = node;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
}

/*
    Finds the inorder successor for a given node

    @param node as the treeNode that is being linked to its successor
    @return treeNode pointer pointing to the successor
*/
treeNode* threadedTree::inorderSuccessor(treeNode* node, treeNode *root) {
    //cout << "***** ENTERING SUCCESSOR *****" << endl;
    if (node->right != nullptr) {
        // If right child exists, find the leftmost node in the right subtree
        return smallestNode(node->right);
    } else {
        // Otherwise, find the in-order successor in the tree
        treeNode* successor = nullptr;
        while (root != nullptr) {
            if (node->val < root-> val) {
                successor = root;
                root = root->left;
            } else if (node->val > root->val) {
                root = root->right;
            } else {
                break;
            }
        }

        //cout << "successor is " << successor -> val << endl;
        //cout << "***** EXITING SUCCESSOR *****" << endl;
        return successor;
    
    
        }


}

/*
    Finds the inorder predecessor of a given node

    @param node as the treeNode that is being linked to its predecessor
    @return treeNode pointer pointing to the predecessor
*/
treeNode* threadedTree::inorderPredecessor(treeNode* node) {
    if(node->left != nullptr) {
        return smallestNode(node->left);
    } else {
        treeNode* cur = node;
        treeNode* parent = findParent(cur->val);
        while(parent != nullptr && parent->right == cur) {
            cur = parent;
        }
        return parent;        

    }
}

/*
    Finds the rightmost node in the tree

    @param node as the node being checked
    @return treeNode pointer of the rightmost node
*/
treeNode* threadedTree::rightMost(treeNode* node) {
    if (node == nullptr)
        return nullptr;
    while (node->right != nullptr && !node->rightThread) {
        node = node->right;
    }
    return node;
}

/*
    Finds the parent of a given node

    @param val as the value being sent from the node
    @return the parent treeNode pointer
*/
treeNode* threadedTree::findParent(int val) {
    if(!contains(val)) {
        return nullptr;
    }
    stack<treeNode*> stk;
    treeNode* cur = root;
    while(cur->val != val) {
        stk.push(cur) ;
        if(cur->val < val) {
            cur = cur->right;
        } else {
            cur = cur->left;   
        }
    }
    return stk.top();    
}
