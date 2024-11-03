/*
474. Ones and Zeroes,
*/

// 遞歸 + 遞推 空間壓縮 TC:O(k*len + k*m*n) len 為字串平均長度 SC:O(2*k + m*n)
class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        int k = strs.size();
        vector<vector<int>> arr(k, vector<int>(2));
        for(int i = 0; i < k; i++) {
            for(int j = 0; j < strs[i].size(); j++) {
                arr[i][0] += strs[i][j] - '0' == 0;
                arr[i][1] += strs[i][j] - '0' == 1;
            }
        }

        // vector<vector<vector<int>>> dp(k+1, vector<vector<int>>(m+1, vector<int>(n+1, INT_MIN/2)));
        // dp[0][0][0] = 0;
        // TC:O(k*m*n) SC:O(m*n)
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
        int res = 0;
        for(int i = 0; i < k; i++) {
            for(int j = m; j >= 0; j--) {
                for(int t = n; t >= 0; t--) {
                    if(arr[i][0] <= j && arr[i][1] <= t) {
                        dp[j][t] = max(dp[j][t], dp[j-arr[i][0]][t-arr[i][1]] + 1);
                    }
                    res = max(res, dp[j][t]);
                }
            }
        }

        return res;

        /*
        遞推 TC:O(k*m*n) SC:O(k*m*n)
        vector<vector<vector<int>>> dp(k+1, vector<vector<int>>(m+1, vector<int>(n+1, INT_MIN/2)));
        dp[0][0][0] = 0;
        int res = 0;
        for(int i = 0; i < k; i++) {
            for(int j = 0; j <= m; j++) {
                for(int t = 0; t <= n; t++) {
                    dp[i+1][j][t] = dp[i][j][t];
                    if(arr[i][0] <= j && arr[i][1] <= t) {
                        dp[i+1][j][t] = max(dp[i+1][j][t], dp[i][j-arr[i][0]][t-arr[i][1]] + 1);
                    }
                    res = max(res, dp[i+1][j][t]);
                }
            }
        }
        */

        /*
        遞歸 TC:O(k*m*n) SC:O(k*m*n)
        vector<vector<vector<int>>> memo(k, vector<vector<int>>(m+1, vector<int>(n+1, -1)));
        function<int(int, int, int)> dfs = [&](int i, int zero, int one) {
            if(i < 0) return 0;
            if(memo[i][zero][one] != -1) return memo[i][zero][one];

            int res = dfs(i-1, zero, one);
            if(zero + arr[i][0] <= m && one + arr[i][1] <= n) {
                res = max(res, dfs(i-1, zero + arr[i][0], one + arr[i][1]) + 1);
            } 

            return memo[i][zero][one] = res;
        };

        return dfs(k-1, 0, 0);
        */
    }
};

// TC:O(k*m*n) SC:O(m*n)
class Solution {
public:
    int findMaxForm(vector<string>& strs, int m, int n) {
        int t = strs.size();
        vector<vector<int>> dp(m+1, vector<int>(n+1));

        for(int i = 0; i < t; i++){
            int zero = 0, one = 0;
            for(auto x:strs[i]){
                if(x == '1') one +=1;
                else zero += 1;
            }
            
            auto dp_tmp = dp;
            for(int c = 0; c <= m; c++){
                for(int d = 0; d <= n; d++){
                    if(zero <= c && one <= d){
                        dp[c][d] = max(dp[c][d], dp_tmp[c-zero][d-one] + 1);
                    }
                }
            }
        }

        return dp[m][n];

    }
};

/*
此題給了你1 & 0的容量
問說在一個數組中最多可以取多少個01010的字串 並且不超過你可以拿的 1 & 0的容量
*/
