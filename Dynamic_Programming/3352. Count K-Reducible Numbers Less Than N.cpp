/*
3352. Count K-Reducible Numbers Less Than N
*/

// TC:O(n*lg(bit數) + n^3 * 2) SC:O(n*n + n)
class Solution {
    using LL = long long;
    LL MOD = 1e9+7;
public:
    int countKReducibleNumbers(string s, int k) {
        int n = s.size();
        vector<int> dp(n);
        vector<vector<LL>> memo(n, vector<LL>(n, -1)); // 走到某個位置的時候還剩下多少個1
        function<LL(int i, bool isLimit, int left1)> dfs = [&](int i, bool isLimit, int left1) -> LL {
            if(i == n) return !isLimit && left1 == 0;
            if(!isLimit && memo[i][left1] != -1) return memo[i][left1];
            LL res = 0;
            int up = isLimit ? s[i]-'0' : 1;
            for(int j = 0; j <= min(left1, up); j++) {
                res = (res + dfs(i+1, isLimit && j == up, left1 - j)) % MOD;
            }

            if(!isLimit) memo[i][left1] = res;
            return res;
        };

        LL res = 0;
        for(int i = 1; i < n; i++) {
            dp[i] = dp[__builtin_popcount(i)] + 1;
            if(dp[i] <= k) {
                res =( res + dfs(0, true, i)) % MOD;
            }
        }

        return res;
    }
};

/*
對一個數字瘋狂開根號 
需要計算機 按一次按鈕就讓數字變很小 ex : 800個1 按一次變成800
暴力 2^800
binary perform s 可能有八百位 問說這之間的可能有多少個可以在ｋ次內變成1

15 -> 1111 會發現就是f(15) = f(4) + 1 都會是之前算過的 dp
4 -> 100 
1 ->
*/
