/*
3366. Minimum Array Sum
*/

// TC:O(n*op1*op2) SC:O(n*op1*op2)
class Solution {
public:
    int minArraySum(vector<int>& nums, int k, int op1, int op2) {
        int n = nums.size();
        vector<vector<vector<int>>> memo(n, vector<vector<int>>(op1+1, vector<int>(op2+1,-1)));
        function<int(int i, int op1_chance, int op2_chance)> dfs = [&](int i, int op1_chance, int op2_chance) -> int {
            if(i == n) return 0;
            if(memo[i][op1_chance][op2_chance] != -1) return memo[i][op1_chance][op2_chance];
            int res = dfs(i+1, op1_chance, op2_chance) + nums[i];
            
            if(op1_chance < op1) {
                int cur = nums[i];
                int nextCur = cur % 2 ? cur/2+1 : cur/2;
                res = min(res, dfs(i+1, op1_chance + 1, op2_chance) + nextCur);
                if(nextCur >= k && op2_chance < op2) {
                    res = min(res, dfs(i+1, op1_chance + 1, op2_chance + 1) + nextCur - k);
                }
            }
            
            if(op2_chance < op2) {
                int cur = nums[i];
                if(cur >= k) {
                    int nextCur = cur - k;
                    res = min(res, dfs(i+1, op1_chance, op2_chance + 1) + nextCur);
                    if(op1_chance < op1) {
                        nextCur = nextCur % 2 ? nextCur/2 + 1 : nextCur/2;
                        res = min(res, dfs(i+1, op1_chance + 1, op2_chance + 1) + nextCur);
                    }
                }
            }
            
            return memo[i][op1_chance][op2_chance] = res;
        };
        
        return dfs(0, 0, 0);
    }
};
