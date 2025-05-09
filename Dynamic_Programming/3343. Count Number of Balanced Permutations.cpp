/*
3343. Count Number of Balanced Permutations
*/

// TC:O(n*n*sum + n*lg(MOD-2)) SC:O(10 + n + n*n*sum)
class Solution {
    using ll = long long;
    ll MOD = 1e9 + 7;
public:
    int countBalancedPermutations(string num) {
        /*
        偶數位置數字總和 == 奇數位置總和
        80! 去枚舉肯定太大 要想個方法讓他變小
        另外可以去想說 我要的總和肯定是 total // 2
        這不就是恰好01背包 通常我們可以求出方案數
        排列問題共通思路:
        拆分成組合問題 + 任意排列問題
        組合: AB, BA是相同的
        組合問題 = 子序列問題 = 01 背包 (for LC. 3343) 他求出的方案數會是組合數
        從一個長度為n 中選出 n / 2 恰好組成 sum/2的方案數
        n1 = floor(n/2)
        n1! * (n - n1)! / c0! *c1! *c2!...c9!
        最終答案: 
        01背包方案數 * n1! * (n - n1)! / c0! *c1! *c2!...c9!
        */
        int n = num.size();
        vector<ll> coins(10);
        ll sum = 0;
        for (int i = 0; i < n; i++) {
            coins[num[i] - '0'] += 1;
            sum += num[i] - '0';
        }
        if (sum % 2) return 0;
        vector<ll> fac(n+1);
        vector<ll> inv(n+1);
        // 建造 階級的 fac 與逆元 
        auto quickMul = [&](ll a, ll b) -> ll {
            ll ans = 1;
            while(b) {
                if(b & 1) {
                    ans = (ans * a) % MOD;
                }
                a = (a*a) % MOD;
                b >>= 1;
            }
            return ans;
        };
        auto build = [&](ll limit) {
            fac[1] = 1;
            for(int i = 2; i <= limit; i++) {
                fac[i] = ((ll) i * fac[i-1]) % MOD;
            }

            inv[limit] = quickMul(fac[limit], MOD-2);
            for(int i = limit - 1; i >= 0; i--) {
                inv[i] = ((ll) (i+1) * inv[i+1]) % MOD;
            }
        };
        build(n);
        vector<vector<vector<ll>>> memo(n, vector<vector<ll>>(n/2+1, vector<ll>(target+1, -1)));
        // auto dfs = [&](this auto &&dfs, int i, int left, int left_sum) -> int {
        //     if(i < 0) {
        //         return (left == 0 && left_sum == sum/2) ? 1 : 0;
        //     }
        //     if(left_sum < 0) return 0;

        //     if(memo[i][left][left_sum] != -1) return memo[i][left][left_sum];
        //     int res = dfs(dfs, i-1, left, left_sum);
        //     int x = num[i]-'0';
        //     if(left) {
        //         res = (res + dfs(dfs, i-1, left-1, left_sum - x)) % MOD;
        //     }
            
        //     return memo[i][left][left_sum] = res;
        // };
        int target = sum / 2;
        vector dp(n / 2 + 1, vector<ll>(target + 1, 0));
        dp[0][0] = 1;
        for (int i = 0; i < n; i++) {
            int x = num[i] - '0';
            auto dp_prev = dp;
            for (int j = 0; j <= n/2; j++) {
                for (int s = 0; s <= target; s++) {
                    if (j < n / 2 && s + x <= target) {
                        dp[j + 1][s + x] = (dp[j + 1][s + x] + dp_prev[j][s])  % MOD;
                    }
                }
            }
        }

        ll ans = ((fac[n/2] * fac[n - n/2]) % MOD * dp[n/2][target]) % MOD;
        for (int i = 0; i < 10; i++) {
            ans = (ans * inv[coins[i]]) % MOD;
        } 
        return ans;
    }
};
