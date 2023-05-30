struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;
}

void addNode(int val) {
    TreeNode* node = new TreeNode;
    node->value = val;
    node->left = nullptr;
    node->right = nullptr;
}

TreeNode* buildTree(int n) {
    if(n < 1) {
        exit(1);
    }
    vector<TreeNode*> nodes(n + 1);
    for(int i = 0; i < n; i++) {
        nodes[i] == addNode(i);
    }
    /*
        I can continue this part! If you could do something with the constructor, destructor, operators, or the threadNode method, that would be great!
     
        Also, I didn't have the header file, so if any method names are wrong, please correct it for me. Thanks!
     */
}

bool isLeaf(TreeNode* node const) {
    if(node == nullptr) {
        return false;
    } else if(node->right == nullptr && node->left == nullptr) {
        return true;
    } else if(node->isThreaded && node->left == nullptr) {
        return true;
    }
    return false;
}

bool threadNode(TreeNode* Node, )
