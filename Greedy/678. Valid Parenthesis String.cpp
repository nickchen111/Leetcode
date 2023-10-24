/*
678. Valid Parenthesis String
*/


// Greedy TC:O(n) SC:O(1)
class Solution {
public:
    bool checkValidString(string s) {
        int countMax = 0;
        int countMin = 0;
        for(int i = 0; i<s.size(); i++){
            if(s[i] == '('){
                countMax++;
                countMin++;
            }
            else if(s[i] == ')'){
                countMax--;
                countMin--;
            }
            else {
                countMax++;
                countMin--;
            }
            
            if(countMax < 0) return false;//都當成左括號還是挽救不了
            if(countMin < 0) countMin = 0;//將一個之前的星號轉變成空格
        }

        return countMin == 0;
    }
};

//DP iterative TC:O(n^3) SC:O(n^2)
class Solution {
public:
    bool checkValidString(string s) {
        int n = s.size();
        vector<vector<bool>> dp(n,vector<bool>(n,0));
        //一個字的狀況
        for(int i = 0; i<n; i++){
            dp[i][i] = (s[i] == '*');
        }

        for(int len = 2; len<=n; len++){
            for(int i = 0; i+len-1<n; i++){
                int j = i+len-1;
                if((s[i] == '(' || s[i] == '*') && (s[j] == ')' || s[j] == '*')){
                    if(len == 2 || dp[i+1][j-1]){
                        dp[i][j] = true;
                        continue;//找到了 直接pass 節省時間
                    }
                }
                //如果不行的話尋找其他分割點
                for(int k = i;k<j;k++){
                    if(dp[i][k] && dp[k+1][j]){
                        dp[i][j] = true;
                        break;
                    }
                }
            }
        }

        return dp[0][n-1];
    }
};

//DP recurion+memo TC:O(n^3) SC:O(n^2)
class Solution {
    vector<vector<int>> memo;
public:
    bool checkValidString(string s) {
        int n = s.size();
        memo = vector<vector<int>>(n,vector<int>(n,-1));

        return dp(s,0,n-1);
    }

    bool dp(string& s, int l, int r){
        if(l > r) return true;
        if(l == r) return s[l] == '*';
        if(memo[l][r] != -1) return memo[l][r];

        if((s[l] == '(' || s[l] == '*') && (s[r] == ')' || s[r] == '*')){
            if(dp(s,l+1,r-1)) return memo[l][r] = true;
        }

        for(int k = l; k<r; k++){
            if(dp(s,l,k) && dp(s,k+1,r)) return memo[l][r] = true;
        }

        memo[l][r] = false;
        return false;
    }
};

/*
此題可以用最簡單的方式去做 用一個count 去計數並不需要真的用一個stack 來省空間
這題的* 可以當作空格 or ( or ) 
follow up 如果只能當作  ( or ) 那就是改成 if countMin < 0 countMin+=2;
*/
