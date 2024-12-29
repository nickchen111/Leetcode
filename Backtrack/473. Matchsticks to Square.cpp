/*
473. Matchsticks to Square
*/

// 2024.12.29 狀壓DP TC:O(3 ^ n) SC:O(2 ^ n)
class Solution {
    using LL = long long;
public:
    bool makesquare(vector<int>& matchsticks) {
        int n = matchsticks.size();
        LL total = reduce(matchsticks.begin(), matchsticks.end(), 0LL);
        if(total % 4) return false;
        vector<LL> nums(1 << n);
        for(int i = 0; i < (1<<n); i++) {
            for(int j = 0; j < n; j++) {
                if((i >> j) & 1) {
                    nums[i] += (LL)matchsticks[j];
                }
            }
        }

        vector<bool> dp((1<<n), 0);
        dp[0] = true;
        for(int i = 1; i < (1 << n); i++) {
            int submask = i;
            if(nums[submask] < total / 4) continue;
            if(nums[submask] % (total / 4)) continue;
            while(submask) {
                if(nums[submask] == total / 4 && dp[submask ^ i]) {
                    dp[i] = true;
                    break;
                }
                submask = (submask - 1) & i;
            }
        }

        return dp[(1<<n) - 1];

        /*
        遞迴 TC:O(3^n) SC:O(2^n)
        vector<int> memo((1<<n), -1);
        auto dfs = [&](auto &&dfs, int mask) -> bool {
            if(mask == 0) return true;
            if(nums[mask] == total / 4) return memo[mask] = true; 
            if(memo[mask] != -1) return memo[mask];
            if(nums[mask] % (total / 4) || nums[mask] < total / 4) return memo[mask] = false;
            int submask = mask;
            while(submask) {
                int remaining_mask = submask ^ mask;
                if(nums[submask] == total / 4 && dfs(dfs, remaining_mask)) return memo[mask] = true;
                submask = (submask - 1) & mask;
            }

            return memo[mask] = false;
        };

        return dfs(dfs, (1<<n) - 1);
        */
        
    }
};


// TC:O(2^n) SC:O(n)
class Solution {
    int target;
    int k = 4;
    bool flag=0;
    vector<bool> visited;
public:
    bool makesquare(vector<int>& matchsticks) {
        int n = matchsticks.size();
        if(n == 0) return false;
        target = accumulate(matchsticks.begin(),matchsticks.end(),0);
        if(target%4 != 0) return false;
        target/=4;

        visited.resize(n);
        sort(matchsticks.begin(),matchsticks.end());
        backtrack(matchsticks,0,0,0);

        return flag;
    }
    void backtrack(vector<int>& matchsticks, int cur, int sum, int count){
        if(sum == target){
            backtrack(matchsticks,0,0,count+1);
            return;
        }
        if(sum > target) return;
        if(count == k){
            flag = true;
            return;
        }
        if(flag) return;
        if(cur == matchsticks.size()) return;

        for(int i = cur; i<matchsticks.size(); i++){
            if(visited[i] == 1) continue;
            if(i > cur && visited[i-1] == 0 && matchsticks[i] == matchsticks[i-1]) continue;
            visited[i] = 1;
            sum+=matchsticks[i];
            backtrack(matchsticks,i+1,sum,count);
            sum-=matchsticks[i];
            visited[i] = 0;
        }
    }
};
