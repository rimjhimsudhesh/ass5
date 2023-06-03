#include <iostream>
#include "threadedTree.h" 
#include <cassert>

using namespace std;

void testThreadedTree() {
    threadedTree tree(10);

    tree.inorderTraverse(tree);

    // Test adding nodes
    tree.add(11);
    tree.add(12);
    tree.remove(2);
    //tree.remove(1); */

    //Iterator iterator;
    //inorderTraverse(tree);
    tree.inorderTraverse(tree);
    

    // Test contains() method
    std::cout << "Tree contains 4: " << (tree.contains(4) ? "true" : "false") << std::endl;
    std::cout << "Tree contains 2: " << (tree.contains(2) ? "true" : "false") << std::endl;
    std::cout << "Tree contains 9: " << (tree.contains(9) ? "true" : "false") << std::endl;
    std::cout << "Tree contains 1: " << (tree.contains(1) ? "true" : "false") << std::endl;
    std::cout << "Tree contains 11: " << (tree.contains(11) ? "true" : "false") << std::endl;
    std::cout << "Tree contains 12: " << (tree.contains(12) ? "true" : "false") << std::endl;
    std::cout << "Tree contains 100: " << (tree.contains(100) ? "true" : "false") << std::endl;//cout << "here";

}

int main() {
    testThreadedTree();

    return 0;
}












