/*
698. Partition to K Equal Sum Subsets
*/

// 2024.12.27 狀壓 TC:O(3^n) SC:O(2^n)
class Solution {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        int n = nums.size();
        int total = reduce(nums.begin(), nums.end(), 0);
        if(total % k) return false;
        int target = total / k;
        vector<int> arr(1 << n);
        for(int i = 0; i < (1 << n); i++) {
            for(int j = 0; j < n; j++) {
                if((i >> j) & 1) arr[i] += nums[j];
            }
        }
        vector<bool> dp((1 << n));
        dp[0] = true;
        for(int i = 1; i < (1<<n); i++) {
            if(arr[i] % target || arr[i] < target) {
                continue;
            }
            for(int j = i; j; j = (j-1) & i) {
                if(arr[j] == target && dp[j ^ i]) {
                    dp[i] = true;
                    break;
                }
            }
        }
        
        return dp[(1<<n) - 1];
        /*
        遞歸 TC:O(3^n) SC:O(2^n)
        vector<int> memo((1 << n), -1);
        auto dfs = [&](auto &&dfs, int mask) -> bool {
            if(arr[mask] == target) return memo[mask] = true;
            if(arr[mask] < target || arr[mask] % target) return memo[mask] = false;
            if(memo[mask] != -1) return memo[mask];
            int submask = mask;
            while(submask) {
                int remaining_mask = submask ^ mask;
                if(arr[submask] == target && dfs(dfs, remaining_mask)) return memo[mask] = true;
                submask = (submask - 1) & mask;
            }

            return memo[mask] = false;
        };
        return dfs(dfs, (1<<n) - 1);
        */
    }
};

//backtrack TC:O(k * 2^n) SC:O(n)
class Solution {
    bool used[16];
    int k;
    int total;
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        total = accumulate(nums.begin(), nums.end(), 0);
        if(total %k != 0) return false;
        this->k = k;
        //DFS 
    
        return DFS(nums, 0, 0, 0);
    }

    bool DFS(vector<int>& nums, int count, int cur, int track){
       
        if(count == k){
            return true;
        }

        if(track == total/k){
            return DFS(nums, count+1, 0, 0);
        }

        if(track > total/k) return false;

        int n = nums.size();
        for(int i = cur; i<n; i++){
            if(used[i] == 1) continue;
            used[i] = 1;
            if(DFS(nums,count,i+1,track+nums[i])) return true;
            used[i] = 0;
        }

        return false;
    }
};


//優化剪枝 
class Solution {
    bool used[16];
    int k;
    int total;
public:
    bool canPartitionKSubsets(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        total = accumulate(nums.begin(), nums.end(), 0);
        if(total %k != 0) return false;
        this->k = k;
        //DFS 
    
        return DFS(nums, 0, 0, 0);
    }

    bool DFS(vector<int>& nums, int count, int cur, int track){
       
        if(count == k){
            return true;
        }

        if(track > total/k) return false;


        if(track == total/k){
            return DFS(nums, count+1, 0, 0);
        }

        int n = nums.size();
        for(int i = cur; i<n; i++){
            if(used[i] == 1) continue;
            if(i > cur && used[i-1] == 0 && nums[i] == nums[i-1]) continue;
            used[i] = 1;
            if(DFS(nums,count,i+1,track+nums[i])) return true;
            used[i] = 0;
        }

        return false;
    }
};


/*
"此題想將數組分成k個相同sum的subsets 沒辦法像之前背包問題416一樣解
只能藉由回溯算法 加上剪枝來儘量減少時間複雜度"
*/
