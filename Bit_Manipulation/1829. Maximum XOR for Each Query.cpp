/*
1829. Maximum XOR for Each Query
*/


// TC:O(n + lgm) m 為冪次數 SC:O(1)
class Solution {
    using LL = long long;
    LL MOD = 1e9 + 7;
public:
    vector<int> getMaximumXor(vector<int>& nums, int maximumBit) {
        int n = nums.size();
        int val = 0;
        auto quickMul = [&](LL a, LL b) {
            LL ans = 1;
            while(b) {
                if(b & 1) ans = ans * a % MOD;
                a = (a*a) % MOD;
                b >>= 1;
            }
            return ans;
        };
        int thre = quickMul(2, maximumBit) - 1;
        for(auto &x : nums) val^=x;
        vector<int> res(n);
        for(int i = 0; i < n; i++) {
            int curAns = val ^ thre;
            res[i] = curAns;
            val ^= nums[n-1-i];
        }

        return res;

    }
};

/*
a ^ a = 0
相同為0 不同為1
*/
