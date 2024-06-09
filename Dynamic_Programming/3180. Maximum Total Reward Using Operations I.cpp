/*
3180. Maximum Total Reward Using Operations I
*/

// DP TC:O(nlgn + n^2) SC:O(n) Max(n) = 2000
class Solution {
public:
    int maxTotalReward(vector<int>& rewardValues) {
        sort(rewardValues.begin(), rewardValues.end());
        int n = rewardValues.size();
        rewardValues.insert(rewardValues.begin(), 0);
        int maxVal = rewardValues.back();
        vector<int> dp(maxVal+1,0);
        dp[0] = 1;
        int res = 0;
        for(int i = 1; i <= n; i++){
            res = max(res, rewardValues[i]);
            auto dp_tmp = dp;
            dp[rewardValues[i]] = 1;
            for(int j = rewardValues[i]-1; j >= 0; j--){
                if(dp_tmp[j]){
                    res = max(res, j + rewardValues[i]);
                    if(j + rewardValues[i] <= maxVal){
                        dp[j + rewardValues[i]] = 1;
                    }
                }
                
            }
        }
        
        return res;
        
    }
};


// Binary Search + Hash Set TC:O(nlgn + n^2) SC:O(n) Max(n) = 2000
class Solution {
public:
    int maxTotalReward(vector<int>& rewardValues) {
        sort(rewardValues.begin(), rewardValues.end());
        int n = rewardValues.size();
        int maxVal = rewardValues.back();
        int res = 0;
        set<int> set;
        set.insert(0);
        for(int i = 0; i < n; i++){
            res = max(res, rewardValues[i]);
            set.insert(rewardValues[i]);
            auto iter = set.lower_bound(rewardValues[i]);
            if(iter != set.begin()){
                iter = prev(iter);
                res = max(res, *iter + rewardValues[i]);
                for(auto itt = iter; itt != set.begin(); itt = prev(itt)){
                    if(*itt + rewardValues[i] <= maxVal) set.insert(*itt + rewardValues[i]);
                }
            }
        }
        
        return res;
        
    }
};


/*
也就是想找一些子序列 他的總和都會比當前那個小 並且最大化所有數字總和
12346
*/
