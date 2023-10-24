/*
509. Fibonacci Number
*/

class Solution {
    // 暴力遞歸
public:
    int fib(int n) {
        if(n == 0 || n ==1) return n;

        return fib(n-1) + fib(n-2);
    }
};

class Solution {
    // 備忘錄
public:
    int fib(int n) {
        int memo[n+1];
        memset(memo, 0, sizeof(memo));

        return dp(memo, n);
    }

    int dp(int memo[], int n){
        if (n == 0 || n == 1) return n;

        if(memo[n] != 0){
            return memo[n];
        }
        memo[n] = dp(memo, n-1) + dp(memo, n-2);

        return memo[n];
    }
};

class Solution {
    // 自底向上用迭代
public:
    int fib(int n) {
        if(n == 0) return 0;
        int *dp = new int[n+1];
        // base case
        dp[0] = 0;
        dp[1] = 1;

        //狀態轉移
        for(int i = 2; i <= n; i++){
            dp[i] = dp[i-1] + dp[i-2];
        }

        return dp[n];
    }
};


class Solution {
    // 優化空間複雜度
public:
    int fib(int n) {
        if(n == 0 || n== 1) return n;
        // base case

        int prev = 0;
        int cur = 1;

        //狀態轉移
        for(int i = 2; i <= n; i++){
            int sum = prev+cur;
            prev = cur;
            cur = sum;
        }

        return cur;
    }
};




/*  
解題方式：
1. 暴力遞歸 tc: o(2^n) sc: o(1)
2. 藉由備忘錄減少時間利用 自頂向下  (动态规划问题的第一个性质：重叠子问题) tc: o(n) sc: o(n)
3. 自底向上 利用迭代 tc: o(n) sc: o(n)
4. 根據方法3 減少空間複雜度 tc: o(n) sc: o(1)

动态规划的核心思想就是穷举求最值(此題不算是動態規劃題 因為沒有要求最值)
重叠子问题、最优子结构、状态转移方程就是动态规划三要素

需明确 base case -> 明确「状态」-> 明确「选择」 -> 定义 dp 数组/函数的含义。
*/
