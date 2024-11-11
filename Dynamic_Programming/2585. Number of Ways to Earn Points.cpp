/*
2585. Number of Ways to Earn Points
*/


// 單調隊列優化DP + 遞推 + 遞歸 + Fail二進制分組
class Solution {
    using LL = long long;
    LL MOD = 1e9 + 7;
public:
    int waysToReachTarget(int target, vector<vector<int>>& types) {
        int n = types.size();

        // 單調隊列空間優化 TC:O(n*target) SC:O(target)
        vector<LL> dp(target+1);
        dp[0] = 1;
        for(int i = 0; i < n; i++) {
            LL w = types[i][1];
            LL c = types[i][0];
            for(int mod = 0; mod <= min((LL)target, w-1); mod++) {
                // deque<int> dq;
                LL sum = 0;
                int cnt = 0;
                for(int j = target-mod; j >= 0 && cnt <= c; j -= w) {
                    // dq.push_front(dp[j]);
                    sum = (sum + dp[j]) % MOD;
                    cnt += 1;
                }
                cnt = c + 1;
                int left = target-mod - w*cnt;
                for(int j = target-mod; j >= 0; j -= w) {
                    // sum = ((sum - dq.back()) % MOD + MOD) % MOD;
                    sum = ((sum - dp[j]) % MOD + MOD) % MOD;
                    // dq.pop_back();
                    dp[j] = (dp[j] + sum) % MOD;
                    // if(target - mod - cnt*w >= 0) {
                    //     dq.push_front(dp[target - mod - cnt*w]);
                    //     sum = (sum + dp[target - mod - cnt*w]) % MOD;
                    // }
                    if(left >= 0) {
                        sum = (sum + dp[left]) % MOD;
                        left -= w;
                    }
                    // cnt += 1;
                }
            }
        }

        return dp[target];
        /*
        嘗試看看單調隊列優化 
        TC:O(n*target) SC:O(n*target)
        vector<vector<LL>> dp(n+1, vector<LL>(target+1, 0));
        dp[0][0] = 1;
        for(int i = 0; i < n; i++) {
            LL w = types[i][1];
            LL c = types[i][0];
            for(int mod = 0; mod <= min((LL)target, w-1); mod++) {
                deque<int> dq;
                LL sum = 0;
                for(int j = mod; j <= target; j += w) {
                    dp[i+1][j] = (dp[i][j] + sum) % MOD;
                    sum = (sum + dp[i][j]) % MOD;
                    dq.push_back(dp[i][j]);
                    if(dq.size() > c) {
                        sum = (((sum - dq.front())% MOD) + MOD) % MOD;
                        dq.pop_front();
                    }
                }
            }
        }

        return dp[n][target];

        */

        /*
        // 嘗試看看二進制分組優化 -> fail 因為會有重複的狀況 例如 1 2 4 6 -> 2+4 跟 單獨6都會是6的狀況
        vector<LL> wgt;
        for(int i = 0; i < n; i++) {
            int c = types[i][0];
            int w = types[i][1];
            for(int k = 1; k <= c; k <<= 1) {
                wgt.push_back(k*w);
                c -= k;
            }
            if(c > 0) {
                wgt.push_back(c*w);
            }
        }

        vector<LL> dp(target+1, 0);
        dp[0] = 1;
        int m = wgt.size();
        for(int i = 0; i < m; i++) {
            for(int j = target; j >= wgt[i]; j--) {
                dp[j] = (dp[j] + dp[j - wgt[i]]) % MOD; 
            }
        }

        return dp[target];
        */

        /*
        遞推 多重背包的空間優化遞推 O(n*k*target) SC: O(target)
        vector<LL> dp(target+1, 0);
        dp[0] = 1;
        for(int i = 0; i < n; i++) {
            for(int j = target; j >= types[i][1]; j--) {
                for(int k = 1; k <= types[i][0]; k++) {
                    if(j-k*types[i][1] >= 0)
                        dp[j] = (dp[j] + dp[j-k*types[i][1]]) % MOD;
                    else break;
                }
            }
        }

        return dp[target];
        */

        /*

        遞推 TC:O(n*target*k) SC:O(n*target)
        vector<vector<LL>> dp(n+1, vector<LL>(target+1,0));
        dp[0][0] = 1;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j <= target; j++) {
                dp[i+1][j] = dp[i][j];
                for(int k = 1; k <= types[i][0]; k++) {
                    if(j-k*types[i][1] >= 0)
                        dp[i+1][j] = (dp[i+1][j] + dp[i][j-k*types[i][1]]) % MOD;
                }
            }
        }

        return dp[n][target];
        */

        /*
        遞歸 TC: O(n*m*target) SC: O(n*m*target)
        vector<vector<LL>> memo(n, vector<LL>(target+1,-1));
        function<LL(int sum, int i)> dfs = [&](int sum, int i) -> LL {
            if(sum > target) return 0;
            if(sum == target) return 1;
            if(i < 0) return 0;
            if(memo[i][sum] != -1) return memo[i][sum];
            int res = 0;
            for(int j = 0; j <= types[i][0]; j++) {
                res = (res + dfs(sum + j*types[i][1], i-1)) % MOD;
            }

            return memo[i][sum] = res;
        };

        return dfs(0, n-1);
        */
    }
};
