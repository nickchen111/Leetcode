/*
926. Flip String to Monotone Increasing
*/

// DP 優化 TC:O(n) SC:O(1)
class Solution {
public:
    int minFlipsMonoIncr(string s) {
        int n = s.size();
        int dp0 = 0;
        int dp1 = 0;
        for(int i = 1; i <= n; i++){
            auto dp0_tmp = dp0, dp1_tmp = dp1;
            if(s[i-1] == '0'){
                dp0 = dp0_tmp;
                dp1 = min(dp0_tmp, dp1_tmp) + 1; 
            }
            else {
                dp0 = dp0_tmp + 1;
                dp1 = min(dp0_tmp, dp1_tmp);
            }
        }

        return min(dp0, dp1);
    }
};


// DP TC:O(n) SC:O(n)
class Solution {
public:
    int minFlipsMonoIncr(string s) {
        int n = s.size();
        vector<vector<int>> dp(n+1, vector<int>(2));
        
        for(int i = 1; i <= n; i++){
            if(s[i-1] == '0'){
                dp[i][0] = dp[i-1][0];
                dp[i][1] = min(dp[i-1][0], dp[i-1][1]) + 1; 
            }
            else {
                dp[i][0] = dp[i-1][0] + 1;
                dp[i][1] = min(dp[i-1][0], dp[i-1][1]);
            }
        }

        return min(dp[n][0], dp[n][1]);
    }
};

// Prefix + Suffix TC:O(n) SC:O(n)
class Solution {
public:
    int minFlipsMonoIncr(string s) {
        int n = s.size();
        vector<int> prefix(n+1); // 1->0
        vector<int> suffix(n+1); // 0->1
        prefix[0] = s[0] - '0';
        suffix[n-1] = '1' - s[n-1];
        for(int i = 1; i < n; i++){
            prefix[i] = prefix[i-1] + s[i] - '0';
        }
        for(int i = n-2; i >= 0; i--){
            suffix[i] = suffix[i+1] + '1' - s[i];
        }

        int res = suffix[0];
        for(int i = 1; i <= n; i++){
            res = min(res, prefix[i-1] + suffix[i]);
        }

        return res;
    }
};

/*
此題想讓一個字串為單調遞增也就是 0000 1111 不可以是 01000110
那要翻幾次裡面的字串才可以達成
我暫時想法是一但發現不是單調遞增每次都看前面的 有多少1以及自己後面有多少個0 選少的那個翻
但這樣的想法算是貪心 題目數據太多無法達到最優解 
另一種方法是 presum suffix 數組 當下每遇到一個就去計算把左邊都變0 右邊都變1所需步驟 然後遍歷過程取最小值
或者直接用DP 這題就可以算是雙狀態的基本型 
*/
