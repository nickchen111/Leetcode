/*
1339. Maximum Product of Splitted Binary Tree
*/

//  TC:O(n) SC:O(n)
class Solution {
    using LL = long long;
    LL total = 0;
    vector<LL> arr;
    LL M = 1e9+7;
public:
    int maxProduct(TreeNode* root) {
        DFS(root,0);
        LL res = 0;
        for(int i = 0; i < arr.size(); i++){
            LL a = total - arr[i];
            res = max(res, a*arr[i]);
        }

        return res % M;
    }
    LL DFS(TreeNode* node, LL sum){
        if(node == NULL){
            return 0;
        }

        LL res = node->val;
        LL left = DFS(node->left, 0);
        LL right = DFS(node->right, 0);
        res += left;
        res += right;
        arr.push_back(res);
        total = max(total, res);
        return res;
    }
};

// 空間優化 時間多跑一次
class Solution {
public:
    // 為了確認總和
    void go(TreeNode* root, long long& sum) {
        if (root == nullptr) return;
        sum += root->val;
        go(root->left, sum);
        go(root->right, sum);
    }
    // 在跑每個節點的時候都將他當作切割點 並且計算最大乘積
    long long go2(TreeNode* root, long long sum, long long& answer) {
        if (root == nullptr) return 0;
        long long s1 = go2(root->left, sum, answer);
        long long s2 = go2(root->right, sum, answer);
        answer = max(answer, (sum - s1) * s1);
        answer = max(answer, (sum - s2) * s2);  
        return s1 + s2 + root->val;      
    }

    int maxProduct(TreeNode* root) {
        long long sum = 0;
        go(root, sum);
        long long answer = 0;
        go2(root, sum, answer);
        return answer % 1000000007;
    }
};


/*
切割樹變成兩個問他們的最大乘績 很顯然按照乘法定理兩個數要盡量接近
我會想說找出切割點並且去嘗試 兩邊之和用可以用減法原理算出
總結就是每一個節點都當成可能的切割點候選人 去紀錄每個點當切割點時他的總和是多少s
*/
