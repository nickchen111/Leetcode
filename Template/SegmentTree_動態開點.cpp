struct SegmentTreeNode {
        int count;
        SegmentTreeNode *left, *right;
        
        SegmentTreeNode() : count(0), left(nullptr), right(nullptr) {}
        
        ~SegmentTreeNode() {
            if (left) delete left;
            if (right) delete right;
        }
    };

    unordered_map<int, SegmentTreeNode*> segmentTrees;
    
    void updateSegmentTree(SegmentTreeNode* &node, int start, int end, int timestamp, int val) {
        if (!node) {
            node = new SegmentTreeNode();
        }
        
        node->count += val;
        
        if (start == end) return;
        
        int mid = start + (end - start) / 2;
        if (timestamp <= mid) {
            updateSegmentTree(node->left, start, mid, timestamp, val);
        } else {
            updateSegmentTree(node->right, mid + 1, end, timestamp, val);
        }
    }
    
    int querySegmentTree(SegmentTreeNode* node, int start, int end, int queryStart, int queryEnd) {
        if (!node) return 0;
        
        if (queryStart > end || queryEnd < start) return 0;
        
        if (queryStart <= start && queryEnd >= end) {
            return node->count;
        }
        
        int mid = start + (end - start) / 2;
        return querySegmentTree(node->left, start, mid, queryStart, queryEnd) + 
               querySegmentTree(node->right, mid + 1, end, queryStart, queryEnd);
    }
