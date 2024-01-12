/*
474. Ones and Zeroes,
*/

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
