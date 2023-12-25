/*
960. Delete Columns to Make Sorted III
*/

// TC:O(n^2*m) SC:O(n)
class Solution {
public:
    int minDeletionSize(vector<string>& strs) {
        int n = strs[0].size(); // col
        vector<int> dp(n,1);
        int maxLen = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < i; j++){
                if(checkLarger(strs,j,i)){
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            maxLen = max(maxLen, dp[i]);
        }

        return n - maxLen;
    }
    bool checkLarger(vector<string>& strs, int idx1, int idx2){
        for(auto &str : strs){
            if(str[idx1] > str[idx2]) return false;
        }

        return true;
    }
};

/*
此題是一個包裝的很好的LIS 問說 每一個字串都要同時刪掉一些idx 讓所有字串刪掉之後剩下的字元會是非遞減的
最少需要刪掉多少個字 ->變相求每個字串的LIS在相同狀況下
*/
