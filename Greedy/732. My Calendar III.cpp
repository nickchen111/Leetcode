/*
732. My Calendar III
*/

// 動態開點lazy 線段樹
struct SegmentTreeNode {
    int val = 0,lazy = 0;
    SegmentTreeNode* left = NULL;
    SegmentTreeNode* right = NULL;
};
void push(SegmentTreeNode* node) {
    if (!node->left) node->left = new SegmentTreeNode();
    if (!node->right) node->right = new SegmentTreeNode();
    if (node->lazy) {
        node->left->lazy += node->lazy;
        node->left->val += node->lazy;;
        node->right->lazy += node->lazy;
        node->right->val += node->lazy;;
    }
    node->lazy = 0;
}
// [L,R]為要更新的區間
void update(SegmentTreeNode* node, int l, int r, int L, int R, int v) {
    if (!node) node = new SegmentTreeNode();
    if (L > r || R < l) return; // 不重疊
    if (L <= l && R >= r) { // 完全包含
        node->val += v;
        node->lazy += v;
        return;
    }
    push(node);
    int m = (l + r) / 2;
    update(node->left, l, m, L, R, v);
    update(node->right, m + 1, r, L, R, v);
    node->val = max(node->left->val, node->right->val);
}
class MyCalendarThree {
    SegmentTreeNode* root;
    int MAX = 1e9;
    int ans = 0;
public:
    MyCalendarThree() {
        root = new SegmentTreeNode();
    }
    
    int book(int startTime, int endTime) {
        update(root, 0, MAX, startTime, endTime-1, 1);
        ans = max(ans, root->val);
        return ans;
    }
};



//sweeping line "TC:O(n^2) SC:O(n)
// 因為傳入一次整包的事件就要n 
// 傳n次呼叫n次函式就是n方"
class MyCalendarThree {
    map<int, int> Map;
public:
    MyCalendarThree() {
        
    }
    
    int book(int startTime, int endTime) {
        Map[startTime] += 1;
        Map[endTime] -= 1;

        int res = 0;
        int sum = 0;
        for(auto& [t, diff]: Map){
            sum+=diff;
            res = max(res, sum);
        }

        return res;
    }
};


 /*
 掃描線的基礎題型
 用hash table去做最方便(map 紅黑樹) 自動幫你排序好起點結束點
 起點就加一代表這個時間點開始有新的事件 結束點就減一代表事件結束
 */
