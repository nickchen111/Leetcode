/*
2172. Maximum AND Sum of Array
*/


// 遞歸 TC:O(n * 2^n) SC:O(2^n)
class Solution {
public:
    int maximumANDSum(vector<int>& nums, int numSlots) {
        int n = nums.size();
        vector<int> memo((1<<(numSlots*2)), -1);
        auto dfs = [&](auto &&dfs, int status, int idx) -> int {
            if(idx == n) return 0;
            if(memo[status] != -1) return memo[status];
            int ret = 0;
            for(int i = 0; i < 2*numSlots; i++) {
                if(((status >> i) & 1)) continue;
                int slot = i/2 + 1;
                ret = max(ret, dfs(dfs, status | (1 << i), idx+1) + (nums[idx]&slot));
            }
            // for(int i = 0; i < n; i++) {
            //     if(((status >> i) & 1) == 0) {
            //         for(int j = 1; j <= numSlots; j++) {
            //             if(visited[j] < 2) {
            //                 visited[j] += 1;
            //                 ret = max(ret, dfs(dfs, status | (1 << i)) + (j&nums[i]) );
            //                 visited[j] -= 1;
            //             }
            //         }
            //     }
            // }
            return memo[status] = ret;
        };
        return dfs(dfs, 0, 0);
    }
};

// 遞推 TC:O(n * 2^n) SC:O(2^n)
class Solution {
public:
    int maximumANDSum(vector<int>& nums, int numSlots) {
        int ans = 0;
        vector<int> f(1 << (numSlots * 2));
        for (int i = 0; i < f.size(); ++i) {
            int c = __builtin_popcount(i);
            if (c >= nums.size()) continue;
            for (int j = 0; j < numSlots * 2; ++j) {
                if ((i & (1 << j)) == 0) { 
                    int s = i | (1 << j);
                    f[s] = max(f[s], f[i] + ((j / 2 + 1) & nums[c]));
                    ans = max(ans, f[s]);
                }
            }
        }
        return ans;
    }
};
