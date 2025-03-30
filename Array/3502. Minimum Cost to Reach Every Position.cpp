// TC:O(n) SC:O(1)
class Solution {
public:
    vector<int> minCosts(vector<int>& cost) {
        /*
        例如想到最後位置 看前面有誰更小就翻他
        */
        int n = cost.size(); 
        int mn = 101;
        vector<int> ans(n);
        for(int i = 0; i < n; i++) {
            mn = min(mn, cost[i]);
            ans[i] = mn;
        }
        return ans;
    }
};
