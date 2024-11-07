/*
3180. Maximum Total Reward Using Operations I
*/
// 遞歸 + 遞推
class Solution {
public:
    int maxTotalReward(vector<int>& rewardValues) {
        int n = rewardValues.size();
        sort(rewardValues.begin(), rewardValues.end());
        vector<int> dp(rewardValues[n-1]+1);
        // TC:O(n * maxVal + nlgn) SC:O(n)
        for(int i = 0; i < n; i++) {
            for(int j = rewardValues[i]-1; j >= 0; j--) {
                j + rewardValues[i] >= rewardValues[n-1] ? dp[rewardValues[n-1]] = max(dp[rewardValues[n-1]], dp[j] + rewardValues[i]) : dp[j + rewardValues[i]] = max(dp[j + rewardValues[i]], dp[j] + rewardValues[i]);
            }
        }

        int res = 0;
        for(int j = 0; j <= rewardValues[n-1]; j++) {
            res = max(res, dp[j]);
        }

        return res;
        /*
        遞推 TC:O(n*maxVal+ nlgn) SC:O(n*maxVal)
        vector<vector<int>> dp(n+1, vector<int>(rewardValues[n-1]+1, INT_MIN/2));
        int res = 0;
        for(int j = 0; j <= rewardValues[n-1]; j++) {
            dp[0][j] = 0;
        }

        for(int i = 0; i < n; i++) {
            for(int j = rewardValues[n-1]; j >= 0; j--) {
                dp[i+1][j] = dp[i][j];
                if(j < rewardValues[i]) {
                    if(j + rewardValues[i] >= rewardValues[n-1]) {
                        dp[i+1][rewardValues[n-1]] = max(dp[i+1][rewardValues[n-1]], dp[i][j] + rewardValues[i]);
                    }
                    else dp[i+1][j + rewardValues[i]] = max(dp[i+1][j + rewardValues[i]], dp[i][j] + rewardValues[i]);
                }
            }
        }

        for(int j = 0; j <= rewardValues[n-1]; j++) {
            res = max(res, dp[n][j]);
        }

        return res;
        */
        /*
        遞歸 TC:O(n*maxVal+ nlgn) SC:O(n*maxVal)
        vector<vector<int>> memo(n, vector<int>(rewardValues[0]+2, -1));
        function<int(int i, int sum, int curMax)> dfs = [&](int i, int sum, int curMax) -> int {
            if(i < 0) return sum;
            if(memo[i][curMax] != -1) return memo[i][curMax];

            return memo[i][curMax] = max(dfs(i-1, sum, curMax), curMax < rewardValues[i] ? dfs(i-1, sum + rewardValues[i], curMax + rewardValues[i] >= rewardValues[0] ? rewardValues[0]+1 : curMax + rewardValues[i]) : INT_MIN);
        };

        return dfs(n-1, 0, 0);
        */
    }
};

// DP TC:O(nlgn + n^2) SC:O(n) Max(n) = 2000
class Solution {
public:
    int maxTotalReward(vector<int>& rewardValues) {
        sort(rewardValues.begin(), rewardValues.end());
        int n = rewardValues.size();
        rewardValues.insert(rewardValues.begin(), 0);
        int maxVal = rewardValues.back();
        vector<int> dp(maxVal+1,0);
        dp[0] = 1;
        int res = 0;
        for(int i = 1; i <= n; i++){
            res = max(res, rewardValues[i]);
            auto dp_tmp = dp;
            dp[rewardValues[i]] = 1;
            for(int j = rewardValues[i]-1; j >= 0; j--){
                if(dp_tmp[j]){
                    res = max(res, j + rewardValues[i]);
                    if(j + rewardValues[i] <= maxVal){
                        dp[j + rewardValues[i]] = 1;
                    }
                }
                
            }
        }
        
        return res;
        
    }
};


// Binary Search + Hash Set TC:O(nlgn + n^2) SC:O(n) Max(n) = 2000
class Solution {
public:
    int maxTotalReward(vector<int>& rewardValues) {
        sort(rewardValues.begin(), rewardValues.end());
        int n = rewardValues.size();
        int maxVal = rewardValues.back();
        int res = 0;
        set<int> set;
        set.insert(0);
        for(int i = 0; i < n; i++){
            res = max(res, rewardValues[i]);
            set.insert(rewardValues[i]);
            auto iter = set.lower_bound(rewardValues[i]);
            if(iter != set.begin()){
                iter = prev(iter);
                res = max(res, *iter + rewardValues[i]);
                for(auto itt = iter; itt != set.begin(); itt = prev(itt)){
                    if(*itt + rewardValues[i] <= maxVal) set.insert(*itt + rewardValues[i]);
                }
            }
        }
        
        return res;
        
    }
};


/*
也就是想找一些子序列 他的總和都會比當前那個小 並且最大化所有數字總和
12346
*/
