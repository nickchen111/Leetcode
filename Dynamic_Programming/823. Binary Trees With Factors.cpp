/*
823. Binary Trees With Factors
*/


// TC:O(n^2) SC:O(n)
class Solution {
public:
    int numFactoredBinaryTrees(vector<int>& arr) {
        // DP 題
        //先sort才能從小問題建構出大問題
        sort(arr.begin(), arr.end());
        long long M = 1e9+7;
        unordered_map<int, long> dp;
        for(int i = 0; i<arr.size(); i++){
            dp[arr[i]] = 1;//每個數自己會是一個tree
            for(int j = 0; j<i; j++){
                if(arr[i]%arr[j]==0 && dp.count(arr[i]/arr[j])){
                    dp[arr[i]] += (dp[arr[j]]*dp[arr[i]/arr[j]])%M;
                }
            }
        }

        long res = 0;
        for(auto map:dp){
            res+=map.second;
        }

        return res%M;
    }
};
