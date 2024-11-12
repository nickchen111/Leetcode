/*
1981. Minimize the Difference Between Target and Chosen Elements
*/

// Bitset or Hash Set or 遞推+遞歸array型背包
class Solution {
public:
    int minimizeTheDifference(vector<vector<int>>& mat, int target) {
        int m = mat.size();
        int n = mat[0].size();
        
        // 最優解 Bitset TC:O(m*n) SC:O(m)
        bitset<805> dp[m];
        int sum = 0;
        for(int i = 0; i < m; i++) {
            int cur = 71;
            for(int j = 0; j < n; j++) {
                if(i == 0) dp[i].set(mat[i][j]);
                else {
                    dp[i] |= (dp[i-1] << mat[i][j]);
                }
                cur = min(cur, mat[i][j]);
            }
            sum += cur;
        }

        int res = INT_MAX;
        for(int j = 0; j <= 804; j++) {
            if(dp[m-1][j]) res = min(res, abs(target-j));
        }

        if(res == INT_MAX) return abs(target - sum);
        return res;

        /*
        用set來做 TC:O(m*n*target) SC:O(target)
        unordered_set<int> set;
        set.insert(0);
        int res = INT_MAX;
        for(int i = 0; i < m; i++) {
            unordered_set<int> tmp;
            // std::set<int> filter;
            int cand = INT_MAX;
            for(int k = 0; k < n; k++) {
                for(auto &s : set){
                    if(s + mat[i][k] > target) cand = min(cand, s + mat[i][k]);
                    else tmp.insert(s + mat[i][k]);
                }
            }
            if(cand != INT_MAX) tmp.insert(cand);
            set.clear();
            set = tmp;
        }
        
        for(auto & s : set) {
            res = min(res, abs(target - s));
        }

        return res;
        */
        /*
        遞推 空間優化 TC:O(m*n*maxVal) SC:O(maxVal)
        int maxVal = 0;
        for(auto &i : mat) {
            for(auto &x : i) {
                maxVal = max(maxVal, x);
            }
        }
        vector<bool> dp(maxVal*m+1);
        dp[0] = 1;
        for(int i = 0; i < m; i++) {
            vector<bool> dp_new(maxVal*m+1);
            for(int k = 0; k < n; k++) {
                for(int j = maxVal*(i+1); j >= mat[i][k]; j--) {
                    if(dp[j - mat[i][k]]) {
                        dp_new[j] = 1;
                    }
                }
            }
            dp = dp_new;
        }
        */
        /*
        遞推
        TC:O(m*n*maxVal) SC:O(m*maxVal)
        vector<vector<bool>> dp(m+1, vector<bool>(maxVal*m+1, 0));
        dp[0][0] = 1;
        for(int i = 0; i < m; i++) {
            for(int k = 0; k < n; k++) {
                for(int j = maxVal*(i+1); j >= mat[i][k]; j--) {
                    if(dp[i][j - mat[i][k]]) {
                        dp[i+1][j] = 1;
                    }
                }
            }
        }
        
        int res = INT_MAX;
        for(int i = 0; i <= maxVal*m; i++) {
            if(dp[i])
                res = min(res, abs(target - i));
        }

        return res;
        */
        /*
        遞歸 TC:O(m*n*maxVal) SC:O(m*maxVal)
        vector<vector<int>> memo(m, vector<int>(70*m+1, -1));
        function<int(int i, int sum)> dfs = [&](int i, int sum) -> int {
            if(i < 0) return abs(sum - target);
            if(memo[i][sum] != -1) return memo[i][sum];
            int res = INT_MAX;
            for(int j = 0; j < n; j++) {
                res = min(res, dfs(i-1, sum + mat[i][j]));
            } 

            return memo[i][sum] = res;
        };

        return dfs(m-1, 0);
        */
    }
};
