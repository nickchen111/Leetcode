/*
3259. Maximum Energy Boost From Two Drinks
*/


// TC:O(n) SC:O(n)
class Solution {
    using LL = long long;
public:
    long long maxEnergyBoost(vector<int>& energyDrinkA, vector<int>& energyDrinkB) {
        int n = energyDrinkA.size();
        vector<vector<LL>> dp(n+1, vector<LL>(2));
        energyDrinkA.insert(energyDrinkA.begin(), -1);
        energyDrinkB.insert(energyDrinkB.begin(), -1);
        dp[1][0] = energyDrinkA[1];
        dp[1][1] = energyDrinkB[1];
        for(int i = 2; i <= n; i++){
            dp[i][0] = max(dp[i-2][1], dp[i-1][0]) + (LL)energyDrinkA[i];
            dp[i][1] = max(dp[i-2][0], dp[i-1][1]) + (LL)energyDrinkB[i];
        }
        
        return max(dp[n][0], dp[n][1]);
    }
};
