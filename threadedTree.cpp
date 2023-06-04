#include "threadedTree.h"
#include <iostream>
#include <stack>

using namespace std;


/*bool treeNode::isLeaf(const treeNode* node) {
    if(node == nullptr) {
        return false;
    } else if(node->right == nullptr && node->left == nullptr) {
        return true;
    } else if(node->threaded && node->left == nullptr) {
        return true;
    }
    return false;
} */

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
    //reeNode* cur = smallestNode(root);
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
    //cout << "building tree..." << endl;
    root = buildTree(1, n);
    cout << root -> val << endl;
    cout << "****** CALLING threadednodes" << endl;
    threadNodes(root);
    cout << "****** DONE threadednodes" << endl;
}

/*
    Threads all nodes in the tree together

    @param inputNode as the beginning node to start threading
*/
void threadedTree::threadNodes(treeNode *inputNode){
    treeNode *currentNode;
    currentNode = inputNode;
    treeNode *smallestValue = smallestNode(root);
    cout << "root is " << root -> val << endl;
    cout << "starting left side" << endl;
    cout << "currentNode " << currentNode -> val << endl;
    cout << "inputNode " << inputNode -> val << endl;

    treeNode *largestValue = rightMost(root);
    if(currentNode -> left != nullptr){
        cout << "going left" << endl;
        threadNodes(currentNode -> left);
    }

    else if(currentNode -> left == nullptr){
        cout << "found place to thread" << endl;
        if(currentNode != smallestValue){
            cout << "threading left..." << endl;
            currentNode -> leftThread = inorderPredecessor(currentNode);
            cout << "left thread value" << currentNode -> leftThread -> val << endl;
        }
    }

    currentNode = inputNode;
    cout << "starting right side" << endl;
    cout << "currentNode " << currentNode -> val << endl;
    cout << "inputNode " << inputNode -> val << endl;


    if(currentNode -> right != nullptr){
        cout << "going right" << endl;
        threadNodes(currentNode -> right);
    }

    else if(currentNode -> right == nullptr){
        cout << "found place to thread" << endl;
        if(currentNode != largestValue){
        cout << "threading right..." << endl;
           currentNode -> rightThread = inorderSuccessor(currentNode, false);
           cout << "right thread value" << currentNode -> rightThread -> val << endl;
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
        cout << "adding value: " << mid << endl;
        cout << "Value " << mid << " added to the tree." << endl;
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
 
 TODO: Finish this comment section! I don't understand it
 @param node
 @param val
 */
treeNode* threadedTree::addHelper(treeNode* node, int val) {
    // Create a new node
    //cout << "created new node" << endl;
    if (node == nullptr) {
        //cout << "node is nullpointer" << endl;
        // If the tree is empty, make the new node the root
        //cout << "makes new node" << endl;
        treeNode* newNode = new treeNode(val, nullptr, nullptr);
        node = newNode;
        //cout << node -> val << endl;
        return node;
    }

    //treeNode* current = node;
    //bool checker = true;
   /* while (current -> val != val) {
        if (val < current->val) {
            cout << "entering val less..." << endl;
            // Go to the left subtree
            /* if (current->leftThread == nullptr) {
                cout << "entering leftThread "
                // Insert the new node as the left child
                newNode->left = current->left;
                newNode->right = current;
                current->left = newNode;
                current->threaded = false;
                cout << "break 1" << endl;
                break;
            } else {
                current = current->left;
            } 
        } else {
            // Go to the right subtree
            if (current->rightThread || current->right == nullptr) {
                // Insert the new node as the right child
                newNode->left = current;
                newNode->right = current->right;
                current->right = newNode;
                current->threaded = false;
                cout << "break 2" << endl;
                break;
            } else {
                current = current->right;
            } 
        }
    } 
 */
        
        if(val < node -> val){
            //cout << "value is going to left with val: ";
            if(node->left == nullptr) {
                node->left = addHelper(node->left, val);
                treeNode* temp = node->leftThread;
                node->leftThread = node->left;
                node->leftThread->rightThread = node;
                node->leftThread->leftThread = temp;
            } else {
                //cout << node->val << endl;
                node -> left = addHelper(node -> left, val);
            }
        } else if(val > node -> val){
            //cout << "value is going to right with val: ";
            if(node -> right == nullptr) {
                node->right = addHelper(node->right, val);
                treeNode* temp = node->rightThread;
                node->rightThread = node->right;
                node->rightThread->leftThread = node;
                node->rightThread->rightThread = temp;
            } else {
                //cout << node->val << endl;
                node -> right = addHelper(node -> right, val);
            }
        } else{
            treeNode* newNode = new treeNode(val, nullptr, nullptr);
            //cout << "threaded to the TBST" << endl;
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
    }else{
        cout << "value found! value is:" << node -> val << endl;
        cout << "node -> right is: " << node -> right -> val << endl;
        cout << "node -> rightThread is: " << node -> rightThread -> val << endl;
        cout << "node -> leftThread is: " << node -> leftThread -> val << endl;
        cout << "node -> left is :" << node -> left -> val << endl;
        if(node -> right != nullptr){
            treeNode *parent = findParent(node -> val);
            parent -> right = node -> right;
            node -> right -> leftThread = parent;
        }
    }




        /* cout << "value found! threading..." << endl;
        if (node->left == nullptr && node->right == nullptr) {
            cout << "node is a leaf" << endl;
            delete node;
            return nullptr;
        }
        if(node->right == nullptr) {
            treeNode* temp = node->left;            
            delete node;
            return temp; 
        }
        if(node->rightThread != nullptr) {
            cout << "value is: " << val << endl;
            treeNode *par = findParent(node -> val);
            cout << "parent val is: " << par -> val << endl;
            par -> leftThread = node -> leftThread;
            node ->leftThread->rightThread = par;
            cout << "left thread done! beginning right thread..." << endl;
        }

        if(node->left == nullptr) {
            cout << "node left == nullptr" << endl;
            treeNode* temp = node->right;            
            delete node;
            return temp;
        } 
        if(node->leftThread != nullptr) {
            treeNode *par = findParent(node -> val);
            node -> leftThread -> rightThread = par;
            cout << "right thread done!" << endl;
        }

        else {
            cout << "finding new node!" << endl;
            treeNode* temp = smallestNode(node->right);
            node->val = temp->val;
            node -> right = removeHelper(node->right, temp->val);
        } */
    
    return node;  

   
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
    /*if(node->right != nullptr) {
        treeNode* farLeft = node->right;
        while(farLeft->left != nullptr) {
            farLeft = farLeft->left;
        }
        node->rightThread = farLeft;
    } else if(node->left != nullptr) {
        treeNode* parent = findParent(node->val);
        node->rightThread = parent;
    }
    */
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

/*
    Finds the inorder successor for a given node

    @param node as the treeNode that is being linked to its successor
    @return treeNode pointer pointing to the successor
*/
treeNode* threadedTree::inorderSuccessor(treeNode* node, bool matchFound) {
    cout << "***ENTERING SUCCESSOR***" << endl;
    /*
    stack<treeNode*> stk;
    treeNode* cur = root;
    while(cur != nullptr || !stk.empty()) {
        while(cur != nullptr) {
            stk.push(cur);
            cur = cur->left;
        }
        cur = stk.top();
        stk.pop();

        if(current == node) {
            if(current->right != nullptr) {
                return current->right;
            } else {
                while(!stk.empty() && !stk.top()->rightThread) {
                    cur = stk.top();
                    stk.pop();
                }
                if(!stk.empty()) {
                    return stk.top()->right;
                } else {
                    return nullptr;
                }
            }
        }
    }
    return nullptr;
    */

    if (node == nullptr) {
        return node;
    }

    if (matchFound)
    {
        cout << "successor is: " << node -> val << endl;
        return node;
    }
    
    if(root -> val == node -> val){
        matchFound = true;
    }
    inorderSuccessor(node->left, matchFound);
   
    cout << root->val << " ";
    
    inorderSuccessor(node->right, matchFound);
    
    cout << "***EXITING SUCCESSOR***" << endl;
    return node;
    
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
        cout << "parent: " << parent -> val << endl;
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
