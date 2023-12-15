/*
2471. Minimum Number of Operations to Sort a Binary Tree by Level
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int minimumOperations(TreeNode* root) {
        if(root == NULL) return 0;
        queue<TreeNode*> q;
        q.push(root);

        int res = 0;
        while(!q.empty()){
            int len = q.size();
            vector<int> arr;
            for(int i = 0; i < len; i++){
                TreeNode* node = q.front();
                q.pop();

                arr.push_back(node->val);
                if(node->left) q.push(node->left);
                if(node->right) q.push(node->right);
            }
            if(arr.size() == 1) continue;
            // 7 6 8 5 -> index sort O(n)
            unordered_map<int,int> rank;
            auto sorted = arr;
            sort(sorted.begin(), sorted.end());
            for(int i = 0; i < sorted.size(); i++){
                rank[sorted[i]] = i;
            }
            for(int i = 0; i < arr.size(); i++){
                while(i != rank[arr[i]]){
                    swap(arr[i], arr[rank[arr[i]]]);
                    res += 1;
                }
            }
            
        }

        return res;
    }
};

/*
此題要你去一層一層看tree 將裡面的數字排序所需最小操作次數加總起來 每一次操作可以選任意同一層的兩個節點
ex: 2 3 4 5 6 7 8 9
    9 8 7 6 5 4 3 2
有想到可能要用index sorting 可是卡在之前的認知覺得此方法只能用在數字規範在數組大小內才可以做
但原來是可以用map記錄想要的位置 然後逐一比對是否在想要的位置上
*/
