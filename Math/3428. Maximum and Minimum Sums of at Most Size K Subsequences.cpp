// 最佳解 by 容斥 + 子序列選or不選DP思想 TC:O(nlgn + n) SC:O(n)
class Solution {
    using LL = long long;
    LL MOD = 1e9 + 7;
public:
    int minMaxSums(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        LL res = 0;
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
            fac[0] = 1;
            for(int i = 2; i <= limit; i++) {
                fac[i] = ((LL) i * fac[i-1]) % MOD;
            }

            inv[limit] = quickMul(fac[limit], MOD-2);
            for(int i = limit - 1; i >= 0; i--) {
                inv[i] = ((LL) (i+1) * inv[i+1]) % MOD;
            }
        };
        build(n);
        int s = 1;
        for(int i = 0; i < n; i++) {
            res = (res + s * (LL)(nums[i] + nums[n-i-1])) % MOD;
            s = (s * 2 - (i < k-1 ? 0 : (fac[i] % MOD * inv[k-1] % MOD * inv[i-k+1] % MOD)) + MOD) % MOD;
            // if(i >= len) {
            //     res = (res + (LL)nums[i] * fac[i] % MOD * inv[len] % MOD * inv[i-len] % MOD) % MOD;
            // }
            // if(n-i-1 >= len) {
            //     res = (res + (LL)nums[i] * fac[n-i-1] % MOD * inv[len] % MOD * inv[n-i-1-len] % MOD) % MOD;
            // }
        }
    
        return res % MOD;
    }
};

// 次佳解 已可以通過 TC:O(nlgn + n) SC:O(n) 對稱性寫法
class Solution {
    using LL = long long;
    LL MOD = 1e9 + 7;
public:
    int minMaxSums(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        LL res = 0;
        vector<LL> fac(n+1);
        fac[0] = 1;
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
        
        // for(int i = 0; i < n; i++) {
        //     res = (res + (LL)nums[i]*2) % MOD;
        // }
        
        for(int len = 0; len <= k-1; len++) {
            for(int i = 0; i < n; i++) {
                if(i >= len) {
                    res = (res + ((LL) (nums[i] + nums[n-i-1]) * fac[i] % MOD * inv[len] % MOD * inv[i-len]) % MOD) % MOD;
                }
            }
        }
        
        return res % MOD;
    }
};



// 次佳解 已可以通過 TC:O(nlgn + n) SC:O(n)
class Solution {
    using LL = long long;
    LL MOD = 1e9 + 7;
public:
    int minMaxSums(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        LL res = 0;
        vector<LL> fac(n+1);
        fac[0] = 1;
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
        
        // for(int i = 0; i < n; i++) {
        //     res = (res + (LL)nums[i]*2) % MOD;
        // }
        
        for(int len = 0; len <= k-1; len++) {
            for(int i = 0; i < n; i++) {
                if(i >= len) {
                    res = (res + (LL)nums[i] * fac[i] % MOD * inv[len] % MOD * inv[i-len] % MOD) % MOD;
                }
                if(n-i-1 >= len) {
                    res = (res + (LL)nums[i] * fac[n-i-1] % MOD * inv[len] % MOD * inv[n-i-1-len] % MOD) % MOD;
                }
            }
        }
        
        return res % MOD;
    }
};
