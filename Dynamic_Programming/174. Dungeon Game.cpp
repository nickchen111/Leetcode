/*
174. Dungeon Game
*/

//iterative TC:O(m*n) SC:O(m*n) 
class Solution {
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        //從結尾往回推
        int m = dungeon.size(); int n = dungeon[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 1));
        dp[m-1][n-1] = 1;//走到終點至少要有一滴血 扣完後
        for(int i = m-1; i>=0; i--){
            for(int j = n-1; j>=0; j--){
                if(i == m-1 && j == n-1){
                    dp[i][j] = 1;//走到終點至少要有一滴血 扣完後
                }
                else if(i == m-1){
                    dp[i][j] = dp[i][j+1]-dungeon[i][j+1];//在邊邊的情況
                }
                else if(j == n-1){
                    dp[i][j] = dp[i+1][j] - dungeon[i+1][j];//邊邊情況
                }
                else dp[i][j] = min(dp[i][j+1]-dungeon[i][j+1], dp[i+1][j] - dungeon[i+1][j]);//右邊下面都可以走

                dp[i][j] = max(dp[i][j], 1);//怕遇到超級補藥 結果扣掉變負數 代表在遇到補藥之前是負數 這是不允許的
            }
        }

        //最後處理一下在0,0的狀況在這點不能落地死亡
        dp[0][0] = dp[0][0] - dungeon[0][0];
        dp[0][0] = max(dp[0][0], 1);//一樣可能剛開始就遇到超級補藥

        return dp[0][0];
    }
};

//recursion+memo
class Solution {
    vector<vector<int>> memo;
public:
    int calculateMinimumHP(vector<vector<int>>& dungeon) {
        //從結尾往回推
        int m = dungeon.size(); int n = dungeon[0].size();
        memo = vector<vector<int>>(m, vector<int>(n, -1));

        return dp(dungeon, 0, 0);
    }

    //定義為 從duegeon[i][j]走到終點需多少體力 dp[i][j]定義為有考慮到踏上格子後的狀態
    int dp(vector<vector<int>>& dungeon, int i, int j){
        int m = dungeon.size(); int n = dungeon[0].size();

        if(i == m-1 && j == n-1) return dungeon[i][j] >=0 ? 1:-dungeon[m-1][n-1]+1;//走這點前確認需多少體力
        if(i >=m || j >=n) return INT_MAX;

        if(memo[i][j] != -1) return memo[i][j];

        int res = min(dp(dungeon, i+1, j), dp(dungeon,i,j+1))-dungeon[i][j];

        memo[i][j] = max(res, 1);

        return memo[i][j];
    }

/*
此題考點
1.求起點出發最少需要多少血到終點 中間過程可能加血or扣血
dp[i][j] 取決於 dp[i][j+1]-dungeon[i][j+1] dp[i+1][j]-dungeon[i+1][j] 定義：已經扣完這格的東西後要走到終點需多少血
2.中間遇到補藥可能會變成負的 這時就取最大 dp[i][j] = max(dp[i][j],1);
*/
