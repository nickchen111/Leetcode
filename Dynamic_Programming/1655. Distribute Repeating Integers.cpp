/*
1655. Distribute Repeating Integers
*/

// TC:O(n * 3^m) SC:O(n * 2^m)
class Solution {
public:
    bool canDistribute(vector<int>& nums, vector<int>& quantity) {
        int m = quantity.size();
        unordered_map<int, int> map;
        vector<int> arr;
        for (auto &num : nums) {
            map[num]++;
        }
        for(auto p : map){
            arr.push_back(p.second);
        }
        int n = arr.size();

        vector<int> sum(1 << m, 0);
        for (int i = 0; i < (1 << m); i++) {
            for (int j = 0; j < m; j++) {
                if ((i >> j) & 1) {
                    sum[i] += quantity[j];
                }
            }
        }

        vector<vector<bool>> dp(1 << m, vector<bool>(n+1, 0));
        dp[0][0] = true;
        for(int i = 0; i < (1<<m); i++) {
            for(int j = 0; j < n; j++) {
                if(dp[i][j]) {
                    dp[i][j+1] = true; 
                } else {
                    for(int s = i; s; s = (s-1)&i) {
                        if(sum[s] <= arr[j] && dp[i^s][j]) {
                            dp[i][j+1] = true;
                            break;
                        }
                    }
                }
            }
        }

        return dp[(1 << m) - 1][n];
        /*
        遞迴 TC:O(n * 3^m) SC:O(n * 2^m)
        vector<vector<int>> memo(1 << m, vector<int>(n, -1));
        auto dfs = [&](auto &&dfs, int mask, int idx) -> bool {
            if (mask == 0) return true;
            if(idx == n) return false;
            if (memo[mask][idx] != -1) return memo[mask][idx];
            int submask = mask;
            
            while(submask) {
                int remain_mask = submask ^ mask;
                if(sum[submask] <= arr[idx]) {
                    
                    if(dfs(dfs, remain_mask, idx+1)) {
                        return memo[mask][idx] = true;
                    }
                    
                }
                submask = (submask - 1) & mask;
            }
            
            return memo[mask][idx] = dfs(dfs, mask, idx+1);
        };

        return dfs(dfs, (1 << m) - 1, 0);
        */
    }
};


/*
n = 1e5 但最多50種interger
問說是否能讓每個客戶拿到他們想拿的元素 並且每位用戶要拿到相同的元素 m = 10 -> 2^10 = 1e3

初始狀態：arr[0] = 9

1. 假設選擇子集 {3}
   - arr[0] = 9 - 3 = 6
   - 遞迴(idx=0) 嘗試用剩下的 6 分配
   - 失敗後回溯，arr[0] 恢復到 9

2. 假設選擇子集 {3,3}
   - arr[0] = 9 - 6 = 3
   - 遞迴(idx=0) 嘗試用剩下的 3 分配
   - 失敗後回溯，arr[0] 恢復到 9

3. 假設選擇子集 {7}
   - arr[0] = 9 - 7 = 2
   - 遞迴(idx=0) 嘗試用剩下的 2 分配
   - 但這時候的問題是...
啊！我明白問題在哪了：
當我們在同一個 idx 繼續遞迴時，即使會回溯，但是在同一層的決策過程中，我們實際上是在用同一個數字去滿足不同的需求組合。這違反了原始問題的要求 - 每個數字應該只能被分配到一個組合中。
比如說，當我們用 9 中的 7 個去滿足了一個需求後，剩下的 2 個不應該再被用來滿足其他需求，而應該：

要嘗試用其他的數字（idx+1）去滿足其他需求
或者嘗試其他的分配方式

這就是為什麼需要在遞迴時用 idx+1：
*/
