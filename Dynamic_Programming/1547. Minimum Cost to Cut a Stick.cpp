/*
1547. Minimum Cost to Cut a Stick
*/

// 遞歸 + 遞推 TC:O(n^3 + nlgn) SC:O(n^2)
class Solution {
public:
    int minCost(int n, vector<int>& cuts) {
        int m = cuts.size();
        cuts.push_back(0);
        cuts.push_back(n);
        sort(cuts.begin(), cuts.end());
        vector<vector<int>> dp(m+2, vector<int>(m+2, 0));
        for(int i = m; i >= 1; i--) {
            // dp[i][i] = cuts[i+1] - cuts[i-1];
            for(int j = i; j <= m; j++) {
                dp[i][j] = INT_MAX/2;
                for(int k = i; k <= j; k++) {
                    dp[i][j] = min(dp[i][j], dp[i][k-1] + dp[k+1][j] + cuts[j+1] - cuts[i-1]);
                }
            }
        }

        return dp[1][m];
        // 遞歸的話可以不用前後加數字，可以遞歸紀錄頭尾長度，也可以加數字，直接用前後index 上的value相減
        // vector<vector<int>> memo(m, vector<int>(m, INT_MAX));
        // function<int(int l, int r, int minLen, int maxLen)> dfs = [&](int l, int r, int minLen, int maxLen) -> int {
        //     // 剩一刀
        //     if(l > r) return 0;
        //     if(l == r) return maxLen - minLen;
        //     if(memo[l][r] != INT_MAX) return memo[l][r];
        //     int res = INT_MAX;
        //     for(int i = l; i <= r; i++) {
        //         res = min(res, dfs(l, i-1, minLen, cuts[i]) + dfs(i+1, r, cuts[i], maxLen) + maxLen - minLen);
        //     }

        //     return memo[l][r] = res;

        // };

        // return dfs(0, m-1, 0, n);
    }
};

/*
題目要求說 給定一個區間 我要切最多100刀 每切一刀就是加上那段的長度
怎麼切會長度加總最小
首先 切的每一刀 可以對應到他要切的那段長度還剩下多少?

數學上來說會發現說 一刀 就是兩段，兩刀 三段，三刀 四段 所以段數肯定就是刀數+1
每切一刀我需要知道目前那刀的長度? 用map 紀錄 當前小於我的位置 他的那段就會是我現在切下去的位置
所以我用了unordered_map 保存了資訊 以及 刀數量 要如何做記憶化?!
還是說切出來的區塊 對應目前切了幾刀 這樣做memo 也不對 
所以想到這題說可以自己排順序~? 這個就詭異了 感覺有貪心的切法 每刀下去我都希望有最小的
所以我會想找中間的去劃分 讓他左右兩邊都可以盡量小 x x x 奇數狀況最好判斷，偶數兩邊都要試試看 
dfs(0, mid-1, 0, cuts[i]) + dfs(mid+1, m-1, cuts[i], n) + curLen
*/
