/*
1335. Minimum Difficulty of a Job Schedule
*/

// TC:O(n^2*d) SC:O(n*d)
class Solution {
public:
    int minDifficulty(vector<int>& jobDifficulty, int d) {
        int n = jobDifficulty.size();
        if(n < d) return -1;
        jobDifficulty.insert(jobDifficulty.begin(), 0);
        vector<vector<int>> dp(n+1, vector<int>(d+1, INT_MAX/2));
        dp[0][0] = 0;

        for(int i = 1; i <= n; i++){
            for(int k = 1; k <= min(d,i); k++){
                //要保留k-1個給前面的分 因為每組至少要有一個
                int maxVal = jobDifficulty[i];
                for(int j = i; j >= k; j--){
                    maxVal = max(maxVal, jobDifficulty[j]);
                    dp[i][k] = min(dp[i][k], dp[j-1][k-1] + maxVal);
                }
            }
        }

        return dp[n][d];

    }
};


/*
分割出d天 每天至少一個任務 每天的數值取決於當天最大值 如何最小化各個subarray的總和是多少
原本想說能否貪心的去做 第一組肯定取最多個元素 那一組的區間會是最大的 看他能怎麼取將一些較大元素包在同個區間內 剩下的自成一國
但很難去判定是要從哪個元素開始貪心的取 分割subarray並且互斥->區間型DP嘗試
區間型I dp[i][k] = dp[j-1][k-1] + max{j:i} 
given an array s[0:i], minimize the sum of each maximum of k subarray
*/
