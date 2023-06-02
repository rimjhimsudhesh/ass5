#include "threadedTree.h"
#include <iostream>

using namespace std;


/*
 Struct for a treeNode object, the nodes used to hold information in the threadedTree
 */
/* struct treeNode {
    int val;
    treeNode* left;
    treeNode* right;
    bool threaded;
}; */


/*
 Iterates through the threadedTree via inorder traversal and prints each node
 
 @param node as the current node to print
 */

// NOTE: I couldnt get this to work either for some random reason. When you compile comment this out to test or 
// you could try to get it working!
/* void Iterator::inorderTraverse(threadedTree& tree) {
    inorderHelper(tree.root);
}

void Iterator::inorderHelper(treeNode* node) {
    if (node != nullptr) {
        inorderHelper(node->left);
        cout << node->val << " ";
        inorderHelper(node->right);
    }
}  */



treeNode::treeNode(int value, treeNode* left, treeNode* right) : val(value), left(left), right(right) {
    this -> threaded = true;
}

treeNode::treeNode() {
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
        //root->val = mid;
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
            if (!current->threaded) {
                current = current->left;
            } else {
                break;
            }
        } else {
            if (current->threaded) {
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
void threadedTree::addHelper(treeNode*& node, int val) {
    // Create a new node
    treeNode* newNode = new treeNode(val, nullptr, nullptr);

    if (node == nullptr) {
        // If the tree is empty, make the new node the root
        node = newNode;
        return;
    }

    treeNode* current = node;
    while (true) {
        if (val < current->val) {
            // Go to the left subtree
            if (current->threaded || current->left == nullptr) {
                // Insert the new node as the left child
                newNode->left = current->left;
                newNode->right = current;
                current->left = newNode;
                current->threaded = false;
                break;
            } else {
                current = current->left;
            }
        } else {
            // Go to the right subtree
            if (current->threaded || current->right == nullptr) {
                // Insert the new node as the right child
                newNode->left = current;
                newNode->right = current->right;
                current->right = newNode;
                current->threaded = false;
                break;
            } else {
                current = current->right;
            }
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
