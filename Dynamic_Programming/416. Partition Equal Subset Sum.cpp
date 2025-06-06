/*
416. Partition Equal Subset Sum
*/

// 位運算優化 TC:O(n * m) m = target / word_size SC:O(m)
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int total = accumulate(nums.begin(), nums.end(), 0);
        if (total % 2 != 0) return false;
        int target = total / 2;
        // 假設 target 最大不會超過 10000，根據題目實際情況調整大小
        bitset<20001> dp;
        dp[0] = 1;
        for (int num : nums) {
            if (num <= target) {
                dp |= (dp << num);
            }
        }
        return dp[target];
    }
};

// 遞推 + 遞歸
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int n = nums.size();
        int total = reduce(nums.begin(), nums.end(), 0);
        if(total % 2) return false;
        vector<bool> dp(total/2+1, 0);
        dp[0] = 1;
        for(int i = 0; i < n; i++) {
            for(int j = total/2; j >= nums[i]; j--) {
                dp[j] = dp[j] || dp[j-nums[i]];
            }
        }
        
        return dp[total/2];
        /*
        遞推
        vector<vector<bool>> dp(n+1, vector<bool>(total/2+1));
        dp[0][0] = true;
        for(int i = 0; i < n; i++) {
            for(int j = total/2; j >= 0; j--) {
                dp[i+1][j] = dp[i][j] || (j - nums[i] >= 0 ? dp[i][j-nums[i]] : false);
            }
        }
        
        return dp[n][total/2];
        */
        /*
        遞歸 TC:O(n*m) SC:O(n*m)
        用1-n個數字是否可以組成 sum
        vector<vector<int>> memo(n+1, vector<int>(total/2+1, -1)); 
        function<bool(int,int)> dfs = [&](int i, int sum)-> bool {
            if(sum > total/2) return false;
            if(i == n) return sum == total/2;
            if(memo[i][sum] != -1) return memo[i][sum] == 0 ? false : true;

            return memo[i][sum] = (dfs(i+1, sum) || dfs(i+1, sum + nums[i]));
        };

        return dfs(0, 0);
        */
    }
};

//一個想法是外層遍歷物品 內層遍歷sum的選項 dp[i] 如果前面可以找到dp2[i-x] 為可以裝得下 那麼 dp[i]肯定可以符合
// TC:O(N*sum) SC:O(sum) N為物品數量
class Solution {
    //空間壓縮
    //需用到兩個dp 
public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(),nums.end(), 0);
        if(sum%2 != 0) return false;//奇數就絕對是無解
        //定義為能否找到一subset可以加到此sum
        vector<int> dp(sum/2+1, false);
        dp[0] = true;

        for(int x:nums){//遍歷物品
            vector<int> dp2 = dp;
            for(int i = 0; i <= sum/2; i++){
                if(i-x>=0 && dp2[i-x] == true){
                    dp[i] = true;
                }
            }
        }

        return dp[sum/2];

    }
};

//如果sum加起來是很稀疏 但是數字給很大的話 可以用set寫
class Solution {
public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(),nums.end(),0);
        if(sum%2 != 0) return false;
        int target = sum/2;

        unordered_set<int> dp;
        dp.insert(0);//加進去的都是可以達到的目標
    
        for(auto x:nums){
            vector<int> temp;
            for(auto s:dp){
                if(s+x == target) return true;
                temp.push_back(s+x);
            }
            for(auto t:temp){
                dp.insert(t);
            }
        }
        
        return false;
    }
};

/*
这里的状态压缩的思想是，在一次遍历中，我们使用 dp 数组表示前面的一些元素是否可以组成和为当前值 i。当我们遍历到第 i 个元素时，
我们需要知道前 i-1 个元素的状态，以便计算出前 i 个元素的状态。但我们不需要知道所有前 i-1 个元素的状态，只需要知道前一个元素的状态，即 dp[i-1]，并基于它来更新当前元素的状态。
由于我们只需要前一个元素的状态，所以可以使用两个 dp 数组，dp 和 dp2，交替更新它们。在每次遍历中，dp 表示前 i-1 个元素的状态，而 dp2 表示前 i 个元素的状态。
这样，可以避免在每次更新状态时覆盖前一个元素的状态，从而实现了空间的优化。所以，虽然理论上你可以使用一个 dp 数组来实现相同的功能，
但这会导致在每次更新状态时需要保留前一个元素的状态，增加了复杂性。使用两个 dp 数组可以更清晰地表示状态的更新，是一种常见的动态规划优化技巧。
*/

/*
01背包問題
一個想法是
外層遍歷物品 內層遍歷sum的選項
dp[i] 如果前面可以找到dp[i-x] 為可以裝得下 那麼 dp[i]肯定可以符合
另一個想法是dp[i][s] 為在 i個物品內 能否加總出s的總和
from the first element i, if there is a way to pick some number whose sum equals to s 
選擇就會是加or 不加
兩種寫法
1. 用已知推估未來
dp[i-1][s] == true -> dp[i][s] == true 不選
dp[i-1][s-nums[i]] == true -> dp[i][s] == true 選
2.用未來推估未來
if(dp[i][s]成立) dp[i+1][s+nums[i+1]]也會成立 
                dp[i+1][s]也成立
此題也可以用DFS做 但會TLE
*/
