/*
3333. Find the Original Typed String II
*/

// TC:O(n + m*k) m 為組數 SC:O(m*k + n)
class Solution {
    using LL = long long;
    LL MOD = 1e9+7;
public:
    int possibleStringCount(string word, int k) {
        int n = word.size();
        if(n < k) return 0;
        vector<LL> cnts;
        LL res = 1;
        LL count = 0;
        for(int i = 0; i < n; i++) {
            count += 1;
            if(i == n-1 || word[i] != word[i+1]) {
                if(cnts.size() < k) {
                    cnts.push_back(count);
                }
                res = (res * count) % MOD;
                count = 0;
            }
        }

        int m = cnts.size();
        if(m >= k) return res;

        vector<vector<LL>> dp(m+1, vector<LL>(k)); // 走到某個位置時 長度小於j的數量
        dp[0][0] = 1;
        vector<LL> presum(k+1);
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < k; j++) {
                presum[j+1] = (presum[j] + dp[i][j]) % MOD;
            }

            // 前面肯定已經有i個了 所以現在至少i+1
            for(int j = i + 1; j < k; j++) {
                dp[i+1][j] = (presum[j] - presum[max(j-cnts[i], 0LL)]) % MOD; 
            }
        }

        res -= accumulate(dp[m].begin() + m, dp[m].end(), 0LL); // 因為之前加總的答案不會有一個字元沒選到的狀況，所以m組至少要從長度m開始計算

        return (res % MOD + MOD) % MOD;
    }
};
