// 分開做01背包 寫法 TC:O(m*n*U) U為max(nums) SC:O(nU)
class Solution {
public:
    int minZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
        if (ranges::all_of(nums, [](int x) { return x == 0; })) {
            return 0;
        }

        int n = nums.size();
        const int MAX_CAP = 10001;
        vector<bitset<MAX_CAP>> dp(n); // vector<vector<int>> dp(n);
        for(int i = 0; i < n; i++) {
            // dp[i].resize(nums[i] + 1);
            dp[i][0] = 1;
        }
        for(int k = 0; k < queries.size(); k++) { // 物品
            auto &q = queries[k];
            int val = q[2];
            for(int i = q[0]; i <= q[1]; i++) { // 需要加入的區間 多個背包
                dp[i] |= (dp[i] << val); // 左移 這是轉成bitset寫法
                /*
                一般背包
                for(int target = nums[i]; target >= val; target--) { // 容量
                    dp[i][target] = dp[i][target] || dp[i][target - val];
                }
                */
            }
            bool check = true;
            for(int i = 0; i < dp.size(); i ++) {
                if (!dp[i].test(nums[i])) { 
                    check = false; 
                    break; 
                }
            }
            if(check) return k + 1;
        }
        return -1;
    }
};



// Bineary Search + 01背包 TC:O(lgm * n * (m + m * target / W)) W為bitset操作時看是32 or 64位一次操作可處理位數
class Solution {
public:
    int minZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        int m = queries.size();
        bool allZero = true;
        for (int x : nums) {
            if (x != 0) { allZero = false; break; }
        }
        if (allZero) return 0;
        
        auto check = [&](int k) -> bool {
            for (int i = 0; i < n; i++) {
                int target = nums[i];
                // 收集前 k 個查詢中覆蓋 cell i 的所有 val
                vector<int> vals;
                int total = 0;
                for (int j = 0; j < k; j++) {
                    int l = queries[j][0], r = queries[j][1], val = queries[j][2];
                    if (l <= i && i <= r) {
                        vals.push_back(val);
                        total += val;
                    }
                }
                // 如果累計值都不足以達到 target，直接返回 false
                if (target > total) return false;
                // 用位元組 dp 來解 subset sum
                // dp[s] = true 表示 s 可達；最大 s 為 target，target 不會超過 10* k (k <= 1000 => 10,000)
                bitset<10001> dp;
                dp[0] = 1;
                for (int v : vals) {
                    dp |= (dp << v);
                    if (dp[target]) break;
                }
                if (!dp[target]) return false;
            }
            return true;
        };
        
        int lo = 0, hi = m + 1;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (check(mid))
                hi = mid;
            else
                lo = mid + 1;
        }
        return lo == m + 1 ? -1 : lo;
    }
};
