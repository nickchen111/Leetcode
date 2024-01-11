/*
1140. Stone Game II
*/

// Top down Recursion 1/11 TC:O(n*2M) SC:O(n*M)
class Solution {
    int dp[105][105];
    int presum[105];
public:
    int stoneGameII(vector<int>& piles) {
        int n = piles.size();
    
        for(int i = 1; i <= n; i++){
            presum[i] = presum[i-1] + piles[i-1];
        }

        return solve(0, 1, piles);
    }
    int solve(int cur, int M, vector<int>& piles){
        if(cur == piles.size()) return 0;
        int n = piles.size();
        if(dp[cur][M] != 0) return dp[cur][M];

        
        for(int x = 1; x <= 2*M; x++){
            if(x + cur - 1 >= n) break;
            
            dp[cur][M] = max(dp[cur][M], presum[n] - presum[cur] - solve(cur+x, max(x,M), piles)); 
        }

        return dp[cur][M];
    }
};

//recursion+memo TC:O(n*2M) SC:O(n*M)
class Solution {
    //recursion+memo
    int memo[101][101];
    int suf[101];//後綴和
public:
    int stoneGameII(vector<int>& piles) {
        int n = piles.size();
        suf[n] = 0;
        //可以去得知剩餘的總合值還有多少 也是可以用前綴和啦
        for(int i = n-1; i>=0; i--){
            suf[i] = suf[i+1] + piles[i];
        }

        return solve(0,1,piles);
    }

    int solve(int i, int M, vector<int>& piles){
        if(i == piles.size()) return 0;//代表沒東西可拿了
        if(memo[i][M] != 0) return memo[i][M];

        //想最大化效益
        int sum = 0;
        for(int x = 1; x<=2*M; x++){
            if(i+x-1 >=piles.size()) break;
            sum+=piles[i+x-1];//看拿幾個就新增幾個 累加上去
            memo[i][M] = max(memo[i][M], sum + suf[i+x] - solve(i+x,max(M,x),piles));
        }

        return memo[i][M];
    }
};

/*
时间复杂度：
在 solve 函数中，有一个嵌套的循环，其中的循环变量 x 的上限是 2M，因此循环体内的操作的时间复杂度是 O(2M)。
solve 函数递归地调用自身，但通过使用记忆化搜索（Memoization），每个状态 (i, M) 最多只会计算一次。在最坏情况下，
需要计算所有可能的状态 (i, M)，总共有大约 n * M 个状态，其中 n 是 piles 数组的长度。
对于每个状态 (i, M)，计算 memo[i][M] 的时间复杂度是 O(2M)。
因此，总的时间复杂度为 O(n * M * 2M)。
*/


/*
此題是說兩邊輪流拿數字 數字總和大的人就贏了 但是每一輪能拿的數字可以高到是上一輪拿的最大值的兩倍或者取這一輪的最大值
所以每輪再拿的時候玩家都會想要最大化自己的總和 並且盡量讓對方拿少一點
maximize: dp(state)
            ||
minimize: max(dp(state'))
dp[i][j]定義為從第i個開始拿 可以最多拿j個 可以得到的最大化利益
return the maximum number of stones Alice can get.
*/
