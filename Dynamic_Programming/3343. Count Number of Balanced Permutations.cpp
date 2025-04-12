/*
3343. Count Number of Balanced Permutations
*/

// TC:O(n*n*sum + n*lg(MOD-2)) SC:O(10 + n + n*n*sum)
class Solution {
    using LL = long long;
    LL MOD = 1e9 + 7;
public:
    int countBalancedPermutations(string num) {

        /*
        排列問題共通思路:
        拆分成組合問題 + 任意排列問題
        組合: AB, BA是相同的
        組合問題 = 子序列問題 = 01 背包 (for LC. 3343)
        從一個長度為n 中選出 n / 2 恰好組成 sum/2的方案數
        n1 = floor(n/2)
        n1 * (n - n1)! / c0! *c1! *c2!...c9!
        最終答案: 
        01背包方案數 * n1 * (n - n1)! / c0! *c1! *c2!...c9!
        */
        int n = num.size();
        vector<int> coins(10); // 物品選擇, 數量
        
        LL sum = 0;
        for(auto x : num) {
            coins[x-'0'] += 1;
            sum += x-'0';
        }
        if(sum % 2) return 0;
        
        vector<LL> fac(n+1);
        vector<LL> inv(n+1);
        // 建造 階級的 fac 與逆元 
        function<LL(LL a, LL b)> quickMul = [&](LL a, LL b) -> LL {
            LL ans = 1;
            while(b) {
                if(b & 1) {
                    ans = (ans * a) % MOD;
                }
                a = (a*a) % MOD;
                b >>= 1;
            }

            return ans;
        };
        auto build = [&](LL limit) {
            fac[1] = 1;
            for(int i = 2; i <= limit; i++) {
                fac[i] = ((LL) i * fac[i-1]) % MOD;
            }

            inv[limit] = quickMul(fac[limit], MOD-2);
            for(int i = limit - 1; i >= 0; i--) {
                inv[i] = ((LL) (i+1) * inv[i+1]) % MOD;
            }
        };
        build(n);
        vector<vector<vector<LL>>> memo(n, vector<vector<LL>>(n/2+1, vector<LL>(sum+1, -1)));
        function<int(int,int,int)> dfs = [&](int i, int left, int left_sum) -> int {
            if(i < 0) {
                return (left == 0 && left_sum == sum/2) ? 1 : 0;
            }
            if(left_sum > sum/2) return 0;

            if(memo[i][left][left_sum] != -1) return memo[i][left][left_sum];
            int res = dfs(i-1, left, left_sum);
            int x = num[i]-'0';
            if(left) {
                res = (res + dfs(i-1, left-1, left_sum+x)) % MOD;
            }
            
            return memo[i][left][left_sum] = res;
        };
        
        
        // vector<LL> dp(sum/2+1);
        // /// 10
        // dp[0] = 1;
        // for(int i = 0; i < 10; i++) {
        //     LL cnt = coins[i].second, val = coins[i].first; 
        //     for(int c = sum/2; c > 0; c--) {
        //         for(int k = 1; k <= cnt; k++) {
        //             if(c < k * val) break;
        //             dp[c] = (dp[c] + dp[c - k * val]) % MOD;
        //         }
        //     }
        // }
        // // cout << dp[sum/2] << endl;
        
        
        LL res = (fac[n/2] * fac[n - n/2]) % MOD;
        res = (res*dfs(n-1, n/2, 0)) % MOD;
        for(int i = 0; i < 10; i++) {
            res = (res*inv[coins[i]]) % MOD;
        }
        
        return res;
       
    }
};

