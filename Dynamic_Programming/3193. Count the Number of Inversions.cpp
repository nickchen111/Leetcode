/*
3193. Count the Number of Inversions
*/

// TC:O(nlgn + n^2*400) SC:O(400*n) n = 300
class Solution {
    using LL = long long;
    LL M = 1e9+7;
public:
    int numberOfPermutations(int n, vector<vector<int>>& requirements) {
        auto cmp = [](const vector<int>& a, const vector<int>& b){
            return a[0] < b[0];
        };
        sort(requirements.begin(), requirements.end(), cmp);
        
        
        vector<vector<LL>> dp(n, vector<LL>(401));// 走到i為止 可以提供的總共對數j的可能性有多少種
        dp[0][0] = 1;
        
        int idx = 0;
        if(requirements[idx][0] == 0) idx++;
        
        for(int i = 1; i < n; i++){
            LL end = 0, count = 0;
            if(idx < requirements.size()){
                end = requirements[idx][0];
                count = requirements[idx][1];
            }
            
            if(end == i){
                if(i >= count){
                    // 當下要提供的對數
                    for(int j = count; j >= 0; j--){
                        dp[i][count] = (dp[i][count] + dp[i-1][count-j]) % M;
                    }
                }
                else {
                    for(int j = i; j >= 0; j--){
                        dp[i][count] = (dp[i][count] + dp[i-1][count-j]) % M;
                    }
                }
                idx++;
            }
            else {
                int total = i*(i+1)/2;
                total = min(400, total);
                for(int j = total; j >= 0; j--){
                    for(int k = 0; k <= i; k++){
                        if(j-k >= 0){
                            dp[i][j] = (dp[i][j] + dp[i-1][j-k]) % M;
                        }
                    }
                }
            }
        }
        int m = requirements.size();
        
        return dp[n-1][requirements[m-1][1]] %M;
        
    }
};



/*
在每個位置分別有需要達到的對數
先將每個位置sort
越後面的對數肯定越多
去思考每個位置可以貢獻對數 最大值:那個位置index 
就可以想到說 如果當前點是指定的index 就從他限制的數量 搭配目前這點可以貢獻的數量 去做DP
如果不是的話 就看當前總共可以累積多少個count 從當前可以累積的conut 與 當下位置可以貢獻的數量 做DP
*/
