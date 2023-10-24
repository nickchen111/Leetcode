/*
746. Min Cost Climbing Stairs
*/

//recursion+memo TC:O(n) SC:O(n)
class Solution {
    vector<int> memo;
public:
    int minCostClimbingStairs(vector<int>& cost) {
        //建立dp當下最好的策略就是看前兩部最好策略的狀況
        int n = cost.size();
        memo = vector<int>(n+1);

        return dp(cost,n);
    }

    int dp(vector<int>& cost, int cur){
        if(cur == 1) return 0;
        if(cur == 0) return 0;
        if(memo[cur]) return memo[cur];
        if(cur-2>=0)
            memo[cur] = min(dp(cost,cur-1)+cost[cur-1],dp(cost,cur-2)+cost[cur-2]);

        return memo[cur];
    }
};

// iterative TC:O(n) SC:O(1)
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        //建立dp當下最好的策略就是看前兩部最好策略的狀況
        int n = cost.size();
        vector<int> dp(n+1);
        dp[0] = 0;
        dp[1] = 0;

        for(int i = 2; i<=n; i++){
            dp[i] = min(dp[i-2]+cost[i-2],dp[i-1]+cost[i-1]);
        }

        return dp[n];
    }
};
