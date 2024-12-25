/*
2572. Count the Number of Square-Free Subsets
*/

// 背包:TC:O(n * M), M = 1024 SC:O(M) 狀壓: TC:O(30 * M) SC:O(M)
using LL = long long;
LL MOD = 1e9 + 7;
const int MX = 30;
const int N_PRIME = 10;
const int M = 1 << N_PRIME;
class Solution {
public:
    int squareFreeSubsets(vector<int>& nums) {
        vector<int> PRIMES = {2,3,5,7,11,13,17,19,23,29};
        vector<LL> SF_MASK(MX+1);
        for(int i = 2; i <= MX; i++) {
            for(int j = 0; j < N_PRIME; j++) {
                if(i % PRIMES[j] == 0) {
                    if(i % (PRIMES[j]*PRIMES[j]) == 0) {
                        SF_MASK[i] = -1;
                        break;
                    }
                    SF_MASK[i] |= (1<<j);
                }   
            }
        }
        int n = nums.size();
        // 狀壓DP TC:O(30 * M) SC:O(M)
        vector<LL> dp(M);
        dp[0] = 1;
        unordered_map<int, LL> map;
        for(auto &num : nums) map[num] += 1;
        for(auto &[num, freq] : map) {
            int mask = SF_MASK[num];
            if(mask == -1) continue;
            if(mask && freq) {
                int other = (M-1) ^ mask; // mask的補集
                int j = other;
                do { // 枚舉other的子集j
                    dp[mask | j] = (dp[mask | j] + dp[j] * freq) % MOD;
                    j = (j-1) & other;
                } while(j != other);
            }
        }
        /*
        背包做法 TC:O(n * M), M = 1024 SC:O(M)
        vector<LL> dp(M);
        dp[0] = 1;
        // vector<vector<LL>> dp(n+1, vector<LL>(M,0));
        // dp[0][0] = 1;
        for(int i = 0; i < n; i++) {
            // for(int state = M - 1; state >= 0; state--) {
            //     dp[i+1][state] = dp[i][state];
            // }
            if(SF_MASK[nums[i]] >= 0) {
                int mask = SF_MASK[nums[i]];
                for(int state = M - 1; state >= mask; state--) {
                    if((mask | state) == state)
                        dp[state] = (dp[state] + dp[state ^ mask]) % MOD;
                }
            }
        }
        */
        auto quickMul = [](long long a, long long b) -> LL{
            long long ans = 1;
            while(b) {
                if(b & 1) ans = (ans*a) % MOD;
                a = (a*a) % MOD;
                b >>= 1;
            }
            return ans;
        };

        LL res = 0;
        for(int j = 0; j < M; j++) {
            res = (res + dp[j]) % MOD;
        }

        return ((res * quickMul(2,map[1])) % MOD - 1 + MOD) % MOD;
        // return (res  - 1 + MOD) % MOD;
    }
};

/*
n = 100, value <= 30
做法1 背包
1. 將數字質因數分解 然後轉成集合的角度去預處理每個數字
2. 做背包 選or不選 選的話 還需要判斷目前的這個集合 是否跟要選的數字是差集 這樣就是n * M, M = 1024的時間複雜度

作法2 狀壓dp 枚舉子集 只枚舉每個數值 並找出他的補集 去枚舉補集的子集
*/
