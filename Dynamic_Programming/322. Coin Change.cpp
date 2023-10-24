/*
322. Coin Change
*/

class Solution {
// 自頂向下
public:
    vector<int> memo;
    int coinChange(vector<int>& coins, int amount) {
        memo = vector<int>(amount+1, -666);//紀錄每種amount狀況下最少需要幾個硬幣可以加總的到 設定為-666之類的負數因為不可能會去存這樣的值

        return dp(coins, amount);
    }
    int dp(vector<int>& coins, int amount){
        //base case
        if(amount == 0) return 0;
        if(amount < 0) return -1;//相減的狀況下讓amount變成負值的話我就return -1代表無效
        if(memo[amount] != -666) return memo[amount];
        
        //狀態轉移方程 
        int ans = INT_MAX;
        for(auto coin:coins){
            // 计算子问题的结果
            int subproblem = dp(coins, amount-coin);
            // 子问题无解则跳过
            if(subproblem < 0) continue;
            // 在子问题中选择最优解，然后加一
            ans = min(ans, subproblem+1);
        }
        memo[amount] = ans == INT_MAX ? -1:ans;

        return memo[amount];

    }
};

class Solution {
    //iterative自底向上
public:
    int coinChange(vector<int>& coins, int amount) {
        //base case 
        if(amount == 0) return 0;
        
        vector<int> dp(amount+1, amount+1); // 数组大小为 amount + 1，初始值也为 amount + 1
        dp[0] = 0;

        //狀態轉移方程
        // 外层 for 循环在遍历所有状态的所有取值
        for(int i = 0; i < dp.size(); i++){
            // 内层 for 循环在求所有选择的最小值
            for(auto coin:coins){
                // 子问题无解，跳过
                if(i - coin < 0) continue;
                dp[i] = min(dp[i], 1 + dp[i-coin]);
            }
        }

        return (dp[amount] == amount+1) ? -1:dp[amount];

    }
};


/*
解題思路：
此題有點像之前解過的給你一數組可以重複取用裡面的數 要你求有多少種可能組合可以總和出target 時間複雜度達到 o(n!)
這題是希望你取的數要達到最小數目 注意到有求為值的味道 可以用dp來解

dp:
思考四件事情 base case 狀態 選擇 dp數組的含義-> 給你任意amount(狀態) 要給我可以總和他的最小硬幣數量

递归算法的时间复杂度分析：子问题总数 x 解决每个子问题所需的时间
子問題總數最多可以到 amount個 代稱n個
解決每個問題所需時間  假設硬幣數量為k種 所以就是o(n*k)
空間複雜度： memo所存的數量 amount+1 即 o(n)
tc: o(n*k) sc: o(n)
*/
