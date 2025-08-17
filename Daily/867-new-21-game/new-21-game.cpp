class Solution {
public:
    double new21Game(int n, int k, int maxPts) {
        if(k == 0 || n >= k + maxPts) return 1.0;
        vector<double> dp(n+1);
        dp[0] = 1.0;
        double sum = 1.0;
        double res = 0.0;

        for(int i = 1; i <= n; i++){
            dp[i] = sum / (double)maxPts;
            if(i < k) sum += dp[i];
            else res += dp[i];
            if(i >= maxPts) sum -= dp[i - maxPts];
        }

        return res;
    }
};

/*
每次隨機獲得1 - mxpts
問說alice 最終會有多少的機會 得到 小於或者等於 n 的點數
這題就是dp
回合數就會是 k 次
*/