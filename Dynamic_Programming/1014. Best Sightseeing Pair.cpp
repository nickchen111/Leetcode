/*
1014. Best Sightseeing Pair
*/


// TC:O(n) SC:O(1)
class Solution {
public:
    int maxScoreSightseeingPair(vector<int>& values) {
        int n = values.size();
        
        int maxVal = values[0]+0;
        int res = 0;
        for(int i = 1; i < n; i++){
            int curMax = values[i] - i + maxVal;
            if(values[i] + i > maxVal){
                maxVal = values[i] + i;
            }
            res = max(res, curMax);
        }
        
        return res;
    }
};

// DP TC:O(n) SC:O(n)
class Solution {
public:
    int maxScoreSightseeingPair(vector<int>& values) {
        int n = values.size();
        vector<int> dp(n);
        int maxVal = values[0]+0;
        int res = 0;
        for(int i = 1; i < n; i++){
            dp[i] = values[i] - i + maxVal;
            if(values[i] + i > maxVal){
                maxVal = values[i] + i;
            }
            res = max(res, dp[i]);
        }
        
        return res;
    }
};

/*
此題要求 兩個idx的最大值滿足以下公式
values[i] + values[j] + i - j
values[i] + i + values[j] - j 
創建兩個數組  values[i] + i  & values[j] - j 
分別找兩個數組的最大值 並且兩個idx不能相同
or 直接開找最大跟次大元素
後來發現不可行 因為必須確認 i < j條件 會不知道如果違反了 該動 i 還是 j
... by dp
動態紀錄比他小的數字value + i最大值 
*/
