/*
3144. Minimum Substring Partition of Equal Character Frequency
*/

// TC:O(26*n^2) SC:O(n)
class Solution {
public:
    int minimumSubstringsInPartition(string s) {
        int n = s.size();
        s = "#" + s; 
        vector<int> dp(n+1,INT_MAX/2);
        dp[0] = 0;
        dp[1] = 1;
        for(int i = 2; i <= n; i++){
            vector<int> count(26);
            for(int j = i; j >= 1; j--){
                count[s[j]-'a'] += 1;
                if(check(count)){
                    dp[i] = min(dp[i], dp[j-1] + 1);
                }
            }
        }
        
        return dp[n];
    }
    bool check(vector<int>& count){
        int tmp = -1;
        for(int i = 0; i < 26; i++){
            if(count[i] == 0) continue;
            else if(tmp != -1 && tmp != count[i]){
                return false;
            }
            else if(tmp == -1){
                tmp = count[i];
            }
        }
        
        return true;
    }
};

/*
將字串拆成每個substring都有相同數量的字元 最少可以拆出幾份
dp[n] : 走到某某為止我可以最少拆成幾個 n = 1000 ， 所以可以回頭遍歷所有的狀態 並且每次要跟之前累加之前還要確定自己目前group是否ok
*/
