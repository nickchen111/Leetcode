/*
300. Longest Increasing Subsequence
最長子序列
*/

// 2025.02.12 all solution
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        int n = nums.size(), ans = 0;
        // 空間O(1) 優化
        int ng = 0;
        for(int i = 0; i < n; i++) {
            int j = lower_bound(nums.begin(), nums.begin() + ng, nums[i]) - nums.begin();
            if(j == ng) {
                nums[ng] = nums[i];
                ng += 1;
            }
            else nums[j] = nums[i];
        }
        return ng;
        /*
        貪心 + 二分
        vector<int> arr;
        for(int i = 0; i < n; i++) {
            auto iter = lower_bound(arr.begin(), arr.end(), nums[i]);
            if(iter == arr.end()) {
                arr.push_back(nums[i]);
            }
            else *iter = nums[i];
        }
        return (int)arr.size();
        */
        /*
        n^2遞推
        vector<int> dp(n,0);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < i; j++) {
                if(nums[j] < nums[i])
                    dp[i] = max(dp[i], dp[j]);
            }
            dp[i] += 1;
            ans = max(ans, dp[i]);
        }
        return ans;
        */
        /*
        遞歸
        vector<int> memo(n, -1);
        auto dfs = [&](auto &&dfs, int i) -> int {
            if(i == n) return 0;
            if(memo[i] != -1) return memo[i];
            int ret = 0;
            for(int j = 0; j < i; j++) {
                if(nums[j] < nums[i])
                    ret = max(ret, dfs(dfs, j));
            }
            return memo[i] = ret + 1;
        };
        int ans = 0;
        for(int i = 0; i < n; i++) {
            ans = max(ans, dfs(dfs, i));
        }
        return ans;
        */
    }
};

//dp解法 TC: O(n ^2) SC: O(n)
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        // base case  dp 数组全都初始化为 1
        // dp[i] 表示以 nums[i] 这个数结尾的最长递增子序列的长度
        vector<int> dp(nums.size(), 1);

        for(int i = 0; i < nums.size(); i++){ //去遍歷來給dp數組賦值
            for(int j = 0; j < i; j++){
                if(nums[i] > nums[j]){
                    dp[i] = max(dp[i], dp[j]+1);
                }
            }
        }

        int ans = 0;
        for(int i = 0; i < dp.size(); i++){
            ans = max(ans, dp[i]);// dp數組中的最大值即為最長遞增子序列
        }

        return ans;
    }
};

//greedy TC:O(nlgn) SC:O(k) 最長子序列長度k
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        //greedy
        vector<int> q;
        for(auto x:nums){
            if(q.empty() || x > q.back()){
                q.push_back(x);
            }
            else{
                auto iter = lower_bound(q.begin(), q.end(), x);
                * iter = x;
            }
        }
        return q.size();
    }
};

/*
此題是要你求最長遞增子序列(LIS) 子序列跟子串不同可以不是連續的
此題也可以從小問題的解推導出大問題 類似數學歸納法 可以用遞歸解 tc: o(n ^2) sc: o(n)
明確選擇 狀態 base case dp數組的定義
dp 數組定義： dp[i] 為 nums[i]這個數做結尾的時候會有的最長遞增子序個數 
base cae: 初始化為一 因為一定至少包含自己
選擇：每次增一個數字的時候 看哪個比他小 去＋1他的dp數組
狀態： 狀態轉移方程 去比較每次新增一個數字後 可以有的最大值對多少 
*/


//此題跟為何不可以用stack記錄呢？？？ 因為用stack的寫法是直接把所有值pop掉 只看從目前要進去的點出發的最長子序列
//跟greedy不同 greedy 只會去取代比他大於等於的值的那個位置然後繼續往後比 不會前面的比他大的值都pop掉
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        // 用單調棧
        stack<int> s;
        for(int i = 0; i < nums.size(); i++){
            while(!s.empty() && s.top() >= nums[i]){
                s.pop();
            }
            s.push(nums[i]);
        }

        return s.size();

    }
};

