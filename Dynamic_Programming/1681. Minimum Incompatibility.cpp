/*
1681. Minimum Incompatibility
*/

// 1223
class Solution {
    // using LL = long long;
public:
    int minimumIncompatibility(vector<int>& nums, int k) {
        int n = nums.size();
        int group = n/k;
        
        unordered_map<int, int> state_value;
        for(int state = 1; state < (1<<n); state++) {
            if(__builtin_popcount(state) != group) continue;
            unordered_set<int> set;
            int mn = INT_MAX;
            int mx = INT_MIN;
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
            if(!set.empty()) {
                state_value[state] = mx - mn;
            }
        }
        vector<int> dp((1<<n), INT_MAX/2);
        dp[0] = 0;
        for(auto state : state_value) {
            dp[state.first] = state.second;
        }

        for(int mask = 0; mask < (1<<n); mask++) {
            if(dp[mask] == INT_MAX/2) continue;
            int sub = ((1<<n) -1) ^ mask;
            int nxt = sub;
            while(nxt) {
                if(state_value.find(nxt) != state_value.end()) {
                    dp[nxt | mask] = min(dp[nxt | mask], dp[mask] + state_value[nxt]);
                }
                nxt = (nxt - 1) & sub;
            }
        }

        return (dp[(1 << n) - 1] == INT_MAX/2) ? -1 : dp[(1 << n) - 1];

        /*
        遞迴 TC:O(3^n) SC:O(2^n)
        vector<int> memo((1<<n), -1);
        auto dfs = [&](auto &&dfs, int mask) -> LL {
            if(mask == 0) return 0; 
            if(memo[mask] != -1) return memo[mask];
            LL ret = INT_MAX/2;
            int submask = mask;
            while(submask) {
                int remain_mask = submask ^ mask;
                if(state_value.find(submask) != state_value.end()) {
                    ret = min(ret, state_value[submask] + dfs(dfs, remain_mask));
                }
                submask = (submask-1) & mask;
            }

            return memo[mask] = ret;
        };
        int res = dfs(dfs, (1<<n) - 1);
        return res == INT_MAX/2 ? -1 : res;
        */
    }
};

/*
將數字分配 每一堆不能有重複數字 並且把最大最小diff 相加 想求最小sum
所以每一堆的數字數量肯定是相同的
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
