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

// 暴力迭代寫法 TC:O(m * n * (m + m * target / w)) SC:O(m)
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
        
        auto check = [&](vector<int>& vals, int target) -> bool {
           
            // bitset寫法
            bitset<10001> dp;
            dp[0] = 1;
            for(int &v : vals) {
                dp |= (dp << v);
                if(dp[target]) return true;
            }
            return false;
            
            /*
            背包寫法
            vector<bool> dp(target + 1);
            dp[0] = true;
            for(int &v : vals) { // 物品
                for(int sum = target; sum >= v; sum--) { // 容量
                    if(dp[sum - v]) dp[sum] = true;
                    if(dp[target]) return true;
                }
            }
            return false;
            */
        };
        for (int k = 0; k < m; k++) {
            bool possible_all = true;
            for(int i = 0; i < n; i++) {
                if(nums[i] == 0) continue;
                int target = nums[i];
                vector<int> vals;
                for(int j = 0; j <= k; j++) {
                    int l = queries[j][0], r = queries[j][1], val = queries[j][2];
                    if(l <= i && i <= r) vals.push_back(val);
                }
                if(!check(vals, target)) {
                    possible_all = false;
                    break;
                }
            }
            if(possible_all) return k+1;
        }
    
        return -1;
    }
};
