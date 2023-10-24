/*
877. Stone Game
*/

//recursion +memo : TC:O(n^2) SC:O(n^2)
class Solution {
    int presum[502];
    int dp[501][501];
public:
    bool stoneGame(vector<int>& piles) {
        int n = piles.size();
        presum[0] = 0;
        
        for(int i = 1; i<=n; i++){
            presum[i] = presum[i-1]+piles[i-1];
        }
        int gain = solve(0, n-1, piles);

        return gain > presum[n]-gain;
    }
    int solve(int i, int j, vector<int>& piles){

        if(i == j) return piles[i];
        if(dp[i][j] != 0) return dp[i][j];

        dp[i][j] = max((presum[j+1]-presum[i] - solve(i+1,j,piles)),presum[j+1]-presum[i]-solve(i,j-1,piles));

        return dp[i][j];
    }
};

//iterative
class Solution {
    int presum[502];
    int dp[501][501];
public:
    bool stoneGame(vector<int>& piles) {
        int n = piles.size();
        presum[0] = 0;
        
        for(int i = 1; i<=n; i++){
            presum[i] = presum[i-1]+piles[i-1];
        }
        //base case
        //只剩一個可以取的狀況
        for(int i = 0; i<n; i++){
            dp[i][i] = piles[i];
        }
        for(int len = 2; len<=n; len++){
            for(int i = 0; i+len-1<n;i++){
                int j = i+len-1;
                if(j-i > 0)//j-i小於等於代表 不能取了 無效
                    dp[i][j] = max(presum[j+1]-presum[i]-dp[i+1][j], presum[j+1]-presum[i]-dp[i][j-1]);
            }
        }

        return dp[0][n-1] > presum[n]-dp[0][n-1];
    }
};

/*
此題在問說先手的人是不是一定贏
此題DP定義要去思考說 如果我取了其中一個那我之後能獲得的最大收益是多少
dp[i][j] 在石頭i~j取頭or尾其中一個 那他之後獲得的最大收益為？
dp[i][j] = pile[i]+ sum[i+1:j]-solve(i+1,j)-> sum[i:j] - solve(i+1,j)
另一種狀況 pile[j] + nsum[i:j-1]-solve(i,j-1)->sum[i:j] - solve(i,j-1)取最大
另外在求區間和的時候用presum概念做 才不會增加時間複雜度
*/
