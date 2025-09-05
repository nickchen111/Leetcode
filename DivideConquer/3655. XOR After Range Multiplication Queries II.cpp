// TC:O(n * sqrtq + qlogM) SC:O(n * sqrtq)
class Solution {
public:
    int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
        long long MOD = 1e9 + 7;
        auto pow = [&](long long x, int n) -> long long {
            long long ans = 1;
            while (n) {
                if (n % 2) {
                    ans = (ans * x) % MOD;
                }
                n /= 2;
                x = x * x % MOD;
            }
            return ans;
        };

        int B = sqrt((int)queries.size());
        int n = nums.size();
        vector<vector<int>> diff(B);

        for (auto q : queries) {
            int l = q[0], r = q[1], k = q[2];
            long long v = q[3];
            // 分塊
            if (k < B) {
                if (diff[k].empty()) diff[k].resize(n + k, 1);
                diff[k][l] = diff[k][l] * v % MOD;
                r = r - (r - l) % k + k;
                diff[k][r] = diff[k][r] * pow(v, MOD - 2) % MOD;
            }
            else {
                for (int i = l; i <= r; i += k) {
                    nums[i] = nums[i] * v % MOD;
                }
            }
        }

        for (int k = 1; k < B; k++) {
            if (diff[k].empty()) continue;
            for (int start = 0; start < k; start++) {
                long long cur = 1;
                for (int i = start; i < n; i += k) {
                    cur = cur * diff[k][i] % MOD;
                    nums[i] = nums[i] * cur % MOD;
                }
            }
        }

        return reduce(nums.begin(), nums.end(), 0, bit_xor());
    }
};
