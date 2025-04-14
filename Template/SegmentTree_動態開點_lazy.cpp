struct SegmentTreeNode {
    int val = 0, lazy = 0;
    SegmentTreeNode* left = nullptr;
    SegmentTreeNode* right = nullptr;
};
void push(SegmentTreeNode* node) {
    if (!node->left) node->left = new SegmentTreeNode();
    if (!node->right) node->right = new SegmentTreeNode();
    if (node->lazy) {
        node->left->val += node->lazy;
        node->left->lazy += node->lazy;
        node->right->val += node->lazy;
        node->right->lazy += node->lazy;
        node->lazy = 0;
    }
}
void update(SegmentTreeNode* &node, int l, int r, int ul, int ur, int val) {
    if (!node) node = new SegmentTreeNode();
    if (ul > r || ur < l) return; // 不重疊
    if (ul <= l && r <= ur) {
        node->val += val;
        node->lazy += val;
        return;
    }

    push(node); // 向下傳遞 lazy
    int mid = (l + r) / 2;
    update(node->left, l, mid, ul, ur, val);
    update(node->right, mid + 1, r, ul, ur, val);
    node->val = max(node->left ? node->left->val : 0, node->right ? node->right->val : 0);
}

// LC. 732 case
class MyCalendarThree {
    SegmentTreeNode* root;
    int MAX = 1e9;
    int res = 0;

public:
    MyCalendarThree() {
        root = new SegmentTreeNode();
    }

    int book(int start, int end) {
        update(root, 0, MAX, start, end - 1, 1);
        res = max(res, root->val);
        return res;
    }
};
