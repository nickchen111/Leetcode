/*
279. Perfect Squares
*/

//我的寫法
class Solution {
    //迭代
public:
    int numSquares(int n) {
        int m = sqrt(n);
        //創建pow
        vector<int> nums;
        vector<int> dp(n+1, INT_MAX);
        for(int i = 1; i<=m; i++){
            nums.push_back(i*i);
            dp[i*i] = 1;
        }
        
        dp[0] = 0;
        for(int i = 1; i <=n; i++){
            for(auto num:nums){
                if(num > i) continue;
                dp[i] = min(dp[i], dp[i-num]+1); 
            }
        }

        return dp[n];
    }
};

//HG大 迭代
class Solution {
public:
    int numSquares(int n) {
        int m = sqrt(n);
        vector<int> dp(n+1, INT_MAX);

        //將完全平方數先算好只要1次
        for(int i = 1; i <= m; i++){
            dp[i*i] = 1;
        }
        dp[0] = 0;

        for(int i = 1; i <= n; i++){
            for(int x = 1; x<= sqrt(i); x++){
                dp[i] = min(dp[i], dp[i-x*x]+1);
            }
        }
        return dp[n];
    }
};


//recursion + memo
class Solution {
    //有沒有辦法用recursion + memo呢
    vector<int> memo;
public:
    int numSquares(int n) {
        int m = sqrt(n);
        vector<int> choices;
        memo = vector<int>(n+1, INT_MAX);//走到某數最少需要多少完全平方數的memo
        for(int i = 1; i<=m; i++){
            choices.push_back(i*i);
        }

        return dp(choices, n);
    }

    int dp(vector<int>& choices, int target){
        if(target == 0) return 0;
        if(target < 0) return -1;

        if(memo[target] != INT_MAX) return memo[target];

        for(auto choice:choices){
            int subProblem = dp(choices, target - choice);
            if(subProblem == -1) continue;
            memo[target] = min(memo[target], subProblem+1);
        }

        return memo[target];
        
    }
};
/*
剛看想不到跟DP關聯性
我的想法 每次來一個數我就除二
創建一vector存 1~n/2 的平方
然後用從後面開始迭代的方式去計算 然後不斷把target-- 但這樣做有點難界定下一次要用什麼數字

看了解析豁然開朗
跟湊零錢題目類似 因為是求最值
n-> sqrt(n)的平方 為集合
1 2 3 ... x
dp[n] -> dp[n-x^2]+1;

tc: O(n^2) sc:O(n)
*/
