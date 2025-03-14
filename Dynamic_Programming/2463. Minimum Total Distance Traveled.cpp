// 2025.03.14 遞推 + 遞歸 
class Solution {
    using ll = long long;
public:
    long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
        ranges::sort(robot), ranges::sort(factory);
        int n = robot.size(), m = factory.size();
        // 空間優化
        vector<ll> dp(n + 1, LLONG_MAX/2);
        dp[0] = 0;
        for(int i = 0; i < m; i++) {
            for(int j = n-1; j >= 0; j--) {
                ll total = factory[i][1], posf = factory[i][0], sum = 0;
                for(int k = j; k >= 0 && total; k--, total--) {
                    sum += abs(posf - (ll)robot[k]);
                    dp[j+1] = min(dp[j+1], sum + dp[k]);
                }
            }
        }
        return dp[n];
        /*
        遞推
        vector dp(m + 1, vector<ll>(n + 1, LLONG_MAX/2));
        dp[0][0] = 0;
        for(int i = 0; i < m; i++) {
            dp[i+1][0] = 0;
            for(int j = 0; j < n; j++) {
                ll total = factory[i][1], posf = factory[i][0], sum = 0;
                dp[i+1][j+1] = dp[i][j+1];
                for(int k = j; k >= 0 && total; k--, total--) {
                    sum += abs(posf - (ll)robot[k]);
                    dp[i+1][j+1] = min(dp[i+1][j+1], sum + dp[i][k]);
                }
            }
        }
        return dp[m][n];
        */
        /*
        遞歸 
        vector memo(n, vector<ll>(m, LLONG_MAX/2));
        auto dfs = [&](auto &&dfs, int i, int j) -> ll {
            if(i < 0) return 0;// 代表機器人修理完了
            if(j == 0) {
                if (factory[j][1] < i + 1) return LLONG_MAX/2;
                else {
                    ll sum = 0;
                    for(int k = 0; k <= i; k++) {
                        sum += abs(factory[j][0] - robot[k]);
                    }
                    return sum;
                }
            }
            ll &ret = memo[i][j];
            if(ret != LLONG_MAX/2) return ret;
            ll total = factory[j][1], posf = factory[j][0];
            ret = dfs(dfs, i, j - 1); // 不選
            ll sum = 0;
            while(i >= 0 && total) {
                sum += abs(posf - (ll) robot[i]);
                total -= 1;
                ret = min(ret, dfs(dfs, i - 1, j - 1) + sum);
                i--;
            }
            return ret;
        };
        return dfs(dfs, n-1, m-1);
        */
    }
};

// 遞推 + 遞歸 
class Solution {
    using LL = long long;
public:
    long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
        int m = robot.size();
        int n = factory.size();

        sort(factory.begin(), factory.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[0] < b[0];
        });
        sort(robot.begin(), robot.end());
        // vector<LL> dp(m+1,LLONG_MAX/2);
        // dp[0] = 0;
        // for(int i = 0; i < n; i++) {
        //     for(int j = m; j >= 0; j--) {
        //         LL cost = 0;
        //         for(int k = 1; k <= factory[i][1] && j - k >= 0; k++) {
        //             cost += abs((LL)robot[j-k] - factory[i][0]);
        //             dp[j] = min(dp[j], dp[j-k] + cost);
        //         }
        //     }
        // }

        // return dp[m];


        vector<LL> presum(n+1);
        for(int i = 0; i < n; i++) {
            presum[i+1] = presum[i] + factory[i][1];
        }
        
        vector<vector<LL>> memo(m, vector<LL>(n, LLONG_MAX/2));
        function<LL(int i, int j)> dfs = [&](int i, int j) -> LL {
            if(i < 0) return 0;
            if(j < 0) return LLONG_MAX/2;

            if(memo[i][j] != LLONG_MAX/2) return memo[i][j];
            if(presum[j+1] < i+1) {
                return LLONG_MAX/2;
            }

            LL res = dfs(i, j-1);
            LL cost = 0;
            for(int k = 1; k <= factory[j][1]; k++) {
                if(i - k + 1 < 0) break;
                cost += abs(robot[i-k+1] - factory[j][0]);

                res = min(res, dfs(i-k, j-1) + cost);
            }

            return memo[i][j] = res;
        };

        return dfs(m-1, n-1);
    }
};

/*
原問題是 n個工廠 修理m個機器人 子問題會是 f(n-1, m-1), f(n-2, m-1) ... f(n-factory[m], m-1)
然後加上各自cost 取最小
*/

/*
這題突破點要先貪心的想到 每個機器人肯定盡量找這他近的 不可能特地跑遠的 然後讓下一個機器人跑到原本離前一個機器人近的
領項交換法可證明

再來問題就變成n個工廠修理m個機器人需要最少多少步可以完成
dp[i][j] 有ｉ個工廠想要處理j個robot 最少有多少距離差總和
*/
