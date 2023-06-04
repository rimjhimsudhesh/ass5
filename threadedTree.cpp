#include "threadedTree.h"
#include <iostream>
#include <stack>

using namespace std;


bool treeNode::isLeaf(const treeNode* node) {
    if(node == nullptr) {
        return false;
    } else if(node->right == nullptr && node->left == nullptr) {
        return true;
    } else if(node->threaded && node->left == nullptr) {
        return true;
    }
    return false;
} 

treeNode::treeNode(int value, treeNode* left, treeNode* right) : val(value), left(left), right(right) {
    this -> threaded = true;
}

treeNode::treeNode() {
}

/*treeNode* threadedTree::threadNodes(treeNode* node) {
    
}*/

/*
 Iterates through the threadedTree via inorder traversal and prints each node
 
 @param node as the current node to print
 */

// NOTE: I couldnt get this to work either for some random reason. When you compile comment this out to test or 
// you could try to get it working!
void threadedTree::inorderTraverse(const threadedTree& tree) {
    treeNode* cur = smallestNode(tree.root);
    inorderHelper(cur);
}

void threadedTree::inorderHelper(treeNode* node) {
    while(node->rightThread != nullptr) {
        cout << node->val << ", ";
        node = node->rightThread;
    }
    cout << node->val << endl;
}   

/* void Iterator::inorderTraverse(){

} */





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
    //cout << "tree built! starting threading..." << endl;
    for(int i = 1; i <= n; i++) {
        treeNode* cur = root;
        //cout << "root established" << endl;
        while(cur->val != i) {
            if(cur->left != nullptr && i < cur->val) {
                cur = cur->left;
            } else if(cur->right != nullptr) {
                cur = cur->right;
            }
        }
        //cout << "while loop done! thread methods beginning..." << endl;
        if(i != n) {
            threadRight(cur);
        } else if(i != 1) {
            threadLeft(cur);
        }
        //cout << "threading complete!" << endl;
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
            if(node->right == nullptr) {
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
    treeNode* threadedTree::removeHelper(treeNode* node, int val){
    if(val < node->val) {
        cout << "value less..." << endl;
        node->left = removeHelper(node->left, val);
    } else if(val > node->val) {
        cout << "value greater..." << endl;
        node->right = removeHelper(node->right, val);
    } else {
        // Case 1: If node is a leaf 🌱
        if(node -> left == nullptr && node -> right == nullptr){
            delete node;
            node = nullptr;
            return node;
        }
        
        // Case 2: one child
        else if(node -> left == nullptr){
            treeNode *parent = findParent(node -> val);
            parent -> left = node -> leftThread;
            node -> leftThread -> rightThread = parent;
            delete node;
            return parent;
        }

        else if(node -> right == nullptr){
            treeNode *parent = findParent(node -> val);
            parent -> left = node -> leftThread;
            node -> leftThread -> rightThread = parent;
            delete node;
            return parent;
        }

        // Case 3: two children
        else{
            treeNode *temp = smallestNode(node -> right);
            node -> val = temp -> val;
            node -> right = addHelper(node -> right, temp -> val);

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
    }
    return node;  

   
}
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

void threadedTree::threadLeft( treeNode* node) {
    //cout << "starting thread left..." << endl;
    /*if(node -> left != nullptr){
        //cout << "entering with left != nullptr" << endl;
        treeNode* farRight = node -> left;
        while(farRight -> right != nullptr) {
            farRight = farRight -> right;
        }

        node -> leftThread = farRight;
        //cout << "left thread to farRight done!" << endl;
    } else if(node->right != nullptr && node != root) {
        //cout << "entering with right != nullptr" << endl;
        treeNode* parent = findParent(node -> val);
        node -> leftThread = parent;
        // cout << "left thread to parent done!" << endl;
    }*/
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

treeNode* threadedTree::findParent(int val) {
    if(!contains(val)) {
        return nullptr;
    }
    stack<treeNode*> stk;
    treeNode* cur = root;
    while(cur->val != val) {
        stk.push(cur);
        if(cur->val < val) {
            cur = cur->right;
        } else {
            cur = cur->left;   
        }
    }
    return stk.top();
}

