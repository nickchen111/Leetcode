/*
二叉搜索樹的增刪查code
*/

//增： 插入一個數
TreeNode* insertIntoBST(TreeNode* root, int val) {
    // 找到空位置插入新节点
    if (root == nullptr) return new TreeNode(val);
    // if (root->val == val)
    //     BST 中一般不会插入已存在元素
    if (root->val < val) 
        root->right = insertIntoBST(root->right, val);
    if (root->val > val) 
        root->left = insertIntoBST(root->left, val);
    return root;
}

//刪：
// 在 BST 中删除节点
TreeNode deleteNode(TreeNode root, int key) {
    // 当根节点为空，则直接返回 null
    if (root == null) return null;
    if (root->val == key) {
        // 当节点为叶子节点或者只有一个子节点时，直接返回该子节点
        if (root->left == null) return root->right;
        if (root->right == null) return root->left;
        // 当节点有两个子节点时，用其右子树最小的节点代替该节点
        TreeNode minNode = getMin(root->right);
        root->right = deleteNode(root->right, minNode->val);
        minNode->left = root->left;
        minNode->right = root->right;
        root = minNode;
    } else if (root_>val > key) {
        // 删除节点在左子树中
        root->left = deleteNode(root->left, key);
    } else if (root->val < key) {
        // 删除节点在右子树中
        root->right = deleteNode(root->right, key);
    }
    return root;
}

// 获取以 node 为根节点的 BST 中最小的节点
TreeNode getMin(TreeNode node) {
    while (node->left != null) node = node->left;
    return node;
}

//查：
TreeNode* searchBST(TreeNode* root, int target) {
    if (root == nullptr) {
        return nullptr;
    }
    // 去左子树搜索
    if (root->val > target) {
        return searchBST(root->left, target);
    }
    // 去右子树搜索
    if (root->val < target) {
        return searchBST(root->right, target);
    }
    return root;
}
