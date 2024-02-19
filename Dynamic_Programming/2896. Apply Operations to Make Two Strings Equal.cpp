/*
2896. Apply Operations to Make Two Strings Equal
*/


// TC:O(n^3) SC:O(n^2) 
class Solution {
public:
    int minOperations(string s1, string s2, int x) {
        vector<int> nums;
        for(int i = 0; i < s1.size(); i++){
            if(s1[i] != s2[i]){
                nums.push_back(i);
            }
        }

        int n = nums.size();
        if(n == 0) return 0;
        if(n%2 == 1) return -1;

        vector<vector<int>> dp(n, vector<int>(n, INT_MAX/2));

        for(int i = 1; i < n; i++){
            dp[i-1][i] = min(x, nums[i] - nums[i-1]);
        }

        for(int len = 4; len <= n; len += 2){
            for(int i = 0; i + len - 1 < n; i++){
                int j = i + len -1;
                // 先assume 是外圍兩個做交換
                dp[i][j] = dp[i+1][j-1] + min(x, nums[j] - nums[i]);
                for(int k = i + 1; k+1 < j; k++){
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k+1][j]);
                }
            }
        }

        return dp[0][n-1];
    }
};

// TC:O(n^2) SC:O(n^2) -> TC:O(n) SC:O(n) 
class Solution {
public:
    int minOperations(string s1, string s2, int x) {
        vector<int> nums;
        for(int i = 0; i < s1.size(); i++){
            if(s1[i] != s2[i]){
                nums.push_back(i);
            }
        }

        int n = nums.size();
        if(n == 0) return 0;
        if(n%2 == 1) return -1;

        vector<vector<int>> dp(n+1, vector<int>(n+1, INT_MAX/2));
        nums.insert(nums.begin(), 0);

        dp[0][0] = 0;
        for(int i = 1; i <= n; i++){
            for(int u = 0; u <= i; u++){
                // 與先前一個配對
                if(i-2 >= 0)
                    dp[i][u] = min(dp[i][u], dp[i-2][u] + nums[i] - nums[i-1]);
                // 與之前某個未配對的配對
                if(u+1 <= i-1)
                    dp[i][u] = min(dp[i][u], dp[i-1][u+1] + 0);
                //自己尚未配對 留給後面配對
                if(u-1 >= 0)
                    dp[i][u] = min(dp[i][u], dp[i-1][u-1] + x);
            }
        }

        return dp[n][0];
    }
};

// O(n)解
class Solution {
public:
    int minOperations(string s1, string s2, int x) {
        vector<int> nums;
        for(int i = 0; i < s1.size(); i++){
            if(s1[i] != s2[i]){
                nums.push_back(i);
            }
        }

        int n = nums.size();
        if(n == 0) return 0;
        if(n%2 == 1) return -1;

        vector<vector<int>> dp(n+1, vector<int>(5, INT_MAX/2));
        nums.insert(nums.begin(), 0);

        dp[0][0] = 0;
        for(int i = 1; i <= n; i++){
            for(int u = 0; u <= 1; u++){
                // 與先前一個配對
                if(i-2 >= 0)
                    dp[i][u] = min(dp[i][u], dp[i-2][u] + nums[i] - nums[i-1]);
                // 與之前某個未配對的配對
                if(u+1 <= i-1)
                    dp[i][u] = min(dp[i][u], dp[i-1][u+1] + 0);
                //自己尚未配對 留給後面配對
                if(u-1 >= 0)
                    dp[i][u] = min(dp[i][u], dp[i-1][u-1] + x);
            }
        }

        return dp[n][0];
    }
};

/*
此題給你兩個binary字串 說你可以做兩個操作
翻s1的任意兩個index 花費cost x
翻s1 i , i+1 相鄰兩個字 花費cost 1
問說最少cost將s1翻成s2 如果不行return -1

給你兩個字串要你幹嘛幹嘛 會想到用two string converging 雙序列DP
此題如果想用貪心策略會發現沒有一個比較適當的方法來做 所以想到DP 會發現我們其實關心的只有不一樣的位置
每個位置會有兩種修改方式 一種是找離他附近的用cost 1 的方式 換一個j-i cost or 直接用cost x flip 會取一個最小的
n^3 解 : 所以就先assume 用cost 1的方式去做交換 然後再對區間找一個切割點 去看如果切割在這裡是否可以有更小的cost
n^2 ： 這個方法比較難懂 要去思考每個元素當下的角色 第一種 直接跟前面一個match or 跟之前的未匹配元素match cost x 但要約定一下
先算在之前的頭上了 第三種 跟誰都不match 直接 + x 往下走

*/
