/*
2742. Painting the Walls
*/

// 遞歸 + 遞推
class Solution {
public:
    int paintWalls(vector<int>& cost, vector<int>& time) {
        int n = time.size();
        int offset = n;
        // vector<vector<int>> dp(n+1, vector<int>(n*2+1, INT_MAX/2));
        // dp[0][offset] = 0;
        // TC:O(n^2) SC:O(n)
        vector<int> dp(2*n+1, INT_MAX/2);
        dp[offset] = 0;
        for(int i = 0; i < n; i++) {
            vector<int> dp_new(2*n+1, INT_MAX/2);
            for(int j = -n; j <= n; j++) {
                if(j + offset -1 >= 0)
                    dp_new[j+offset-1] = min(dp_new[j+offset-1], dp[j+offset]);
                int nxt = j + offset + time[i] >= 2*n ? 2*n : j + offset + time[i];
                dp_new[nxt] = min(dp_new[nxt], dp[j+offset] + cost[i]);   
            }
            dp = dp_new;
        }

        int res = INT_MAX/2;
        for(int j = offset; j <= 2*n; j++) {
            res = min(res, dp[j]);
        }

        return res;
        /*
        遞歸 TC:O(n*n) SC:O(n*n)
        vector<vector<int>> memo(n, vector<int>(n*2+1, -1));
        auto dfs = [&](auto &&dfs, int i, int leftTime) -> int {
            if(i == n) return leftTime >= 0 ? 0 : INT_MAX/2;
            // x x x x x 
            if(leftTime - (n-i) >= 0) return 0;
            if(memo[i][leftTime + offset] != -1) return memo[i][leftTime + offset];
            int res = dfs(dfs, i+1, leftTime - 1);
            res = min(res, dfs(dfs, i+1, leftTime + time[i]) + cost[i]);

            return memo[i][leftTime + offset] = res;
        };

        return dfs(dfs, 0, 0);
        */
    }
};


/*
也就是說你可以選or不選 paid painter for 某面牆
如果不選 就要用free painer 但是這代表之前已經有牆正在被pain
選了的話就可以累加時間上去 
n = 500 大致上代表 可以用n^3去做
所以代表說 當你想塗油漆到底時 你要是>=0的時間
dfs(int i, int lefttime, int cost) time準備1000就夠了
*/
