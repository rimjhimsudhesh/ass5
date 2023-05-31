#include <iostream>
#include "threadedTree.h" // Assuming you have a header file for the threadedTree class

int main() {
    // Create a threaded tree with some nodes
    threadedTree myTree(5);
    /* myTree.insert(5);
    myTree.insert(3);
    myTree.insert(7);
    myTree.insert(2);
    myTree.insert(4);
    myTree.insert(6);
    myTree.insert(8);
 */
    // Print the tree
    std::cout << "Original Tree:" << std::endl;
    std::cout << myTree << std::endl;

    // Clear the tree
    //myTree.clear(5);

    // Print the tree after clearing
    std::cout << "Tree after clearing:" << std::endl;
    std::cout << myTree << std::endl;

    return 0;
}






