/*
1681. Minimum Incompatibility
*/

// TC:O(n * 2^n + 3^n) SC:O(2^n)
class Solution {
public:
    int minimumIncompatibility(vector<int>& nums, int k) {
        int n = nums.size();
        int group = n/k;
        unordered_map<int,int> value;
        for(int state = 1; state < (1<<n); state++) {
            if(__builtin_popcount(state) != group) continue;
            unordered_set<int> set;
            int mx = INT_MIN;
            int mn = INT_MAX;
            for(int i = 0; i < n; i++) {
                if((state >> i) & 1) {
                    if(set.find(nums[i]) != set.end()) {
                        set.clear();
                        break;
                    }
                    set.insert(nums[i]);
                    mx = max(mx, nums[i]);
                    mn = min(mn, nums[i]);
                }
            }
            if(!set.empty()) value[state] = mx - mn;
        }
        unordered_map<int,int> memo;
        auto dfs = [&](auto &&dfs, int state) -> int {
            if(state == 0) return 0; // 都選完了
            if(memo.find(state) != memo.end()) return memo[state];
            long long res = INT_MAX;
            for(int sub = state; sub > 0; sub = (sub-1)&state) {
                if(value.find(sub) != value.end()) {
                    res = min(res, (long long) value[sub] + dfs(dfs, state ^ sub));
                }
            }

            return memo[state] = res;
        };
        int ret = dfs(dfs, (1<<n)-1);
        return ret == INT_MAX ? -1 : ret;
    }
};
