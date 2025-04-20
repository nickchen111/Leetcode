/*
307. Range Sum Query - Mutable
*/

/*
計算區間和 TC:O(lgn)
改index數值 : TC:O(lgn)
*/
class NumArray {
    class SegTreeNode{
    public:
        SegTreeNode* left;
        SegTreeNode* right;
        int start, end;
        int info;
        SegTreeNode(int a, int b): left(NULL), right(NULL), start(a), end(b), info(0){}
    };

    void init(SegTreeNode* node, int a, int b){
        if(a == b){
            node->info = nums[a];
            return;
        }
        int mid = (a+b)/2;
        //建立起節點
        if(node->left == NULL){
            node->left = new SegTreeNode(a,mid);
            node->right = new SegTreeNode(mid+1,b);
        }
        //初始化裡面的數值
        init(node->left, a, mid);
        init(node->right, mid+1, b);
        node->info = node->left->info + node->right->info;
    }

    void UpdateSingle(SegTreeNode* node, int index, int val){
        //如果根本不在線段樹的守備範圍內
        if(index < node->start || index > node->end){
            return;
        }
        //如果找到了此點
        if(node->start == index && node->end == index){
            node->info = val;
            return;
        }
        //遍歷
        UpdateSingle(node->left, index, val);
        UpdateSingle(node->right, index, val);
        //後序位置
        node->info = node->left->info + node->right->info;
    }

    int QueryRange(SegTreeNode* node, int a, int b){
        //不在我的守備範圍內 互斥
        if(b < node->start || a > node->end){
            return 0; 
        }
        //目前這段為要找範圍的子集->完全包含
        if(a<=node->start && b>=node->end){
            return node->info;
        }

        return QueryRange(node->left, a, b) + QueryRange(node->right, a, b);
    }

    SegTreeNode* root;
    vector<int> nums;
public:
    NumArray(vector<int>& nums) {
        this->nums = nums;
        root = new SegTreeNode(0, nums.size()-1);
        init(root, 0, nums.size()-1);

    }
    
    void update(int index, int val) {
        UpdateSingle(root, index, val);
    }
    
    int sumRange(int left, int right) {
        return QueryRange(root, left, right);
    }
};
