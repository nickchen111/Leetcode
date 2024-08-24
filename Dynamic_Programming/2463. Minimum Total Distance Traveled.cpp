/*
2463. Minimum Total Distance Traveled
*/

// 遞歸 TC:O(nm^2) SC:O(m*n)
class Solution {
    using LL = long long;
    int m, n;
    vector<vector<LL>> memo;
    vector<int> robot;
    vector<vector<int>> factory;
public:
    long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
        m = robot.size();
        n = factory.size();
        sort(factory.begin(), factory.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[0] < b[0];
        });
        sort(robot.begin(), robot.end());
        this -> robot = robot;
        this -> factory = factory;

        memo.resize(n, vector<LL>(m, -1));

        return helper(0,0);
    }
    LL helper(int i, int j){
        if(j == m) return 0;

        if(i == n-1){
            if(m-j > factory[i][1]) return LLONG_MAX/2;
            LL res = 0;
            for(int k = j; k < m; k++){
                res += abs(robot[k] - factory[i][0]);
            }
            
            return res;
        }

        if(memo[i][j] != -1) return memo[i][j];

        LL res = helper(i+1, j); //  不選 -> 這次工場不製造任何機器人
        LL k = 1, cost = 0;
        while(k <= factory[i][1] && j + k - 1 < m){
            cost += abs((LL)robot[j+k-1] - factory[i][0]);
            res = min(res, cost + helper(i+1,j+k));
            k++;
        }

        return memo[i][j] = res;
    }
};

// 遞推 TC:O(nm^2) SC:O(m)
class Solution {
    using LL = long long;
    int m, n;
public:
    long long minimumTotalDistance(vector<int>& robot, vector<vector<int>>& factory) {
        m = robot.size();
        n = factory.size();
        sort(factory.begin(), factory.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[0] < b[0];
        });
        sort(robot.begin(), robot.end());
        
        vector<LL> dp(m+1, LLONG_MAX/2);
        dp[0] = 0;
        // n個工廠
        for(int i = 0; i < n; i++){
            // 處理m個robot
            for(int j = m; j > 0; j--){
                LL cost = 0;
                for(int k = 1; k <= min(factory[i][1], j); k++){
                    cost += abs((LL) robot[j-k] - factory[i][0]);
                    dp[j] = min(dp[j], cost + dp[j-k]);
                }
            }
        }

        return dp[m];
    }
};

/*
這題突破點要先貪心的想到 每個機器人肯定盡量找這他近的 不可能特地跑遠的 然後讓下一個機器人跑到原本離前一個機器人近的
領項交換法可證明

再來問題就變成n個工廠修理m個機器人需要最少多少步可以完成
dp[i][j] 有ｉ個工廠想要處理j個robot 最少有多少距離差總和
*/
