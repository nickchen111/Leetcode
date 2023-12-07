/*
1363. Largest Multiple of Three
*/


// 未優化 空間使存取內容較多 較冗余 TC:O(nlgn + 3*n) SC:O(3*n)
class Solution {
public:
    string largestMultipleOfThree(vector<int>& digits) {
        int n = digits.size();
        sort(digits.rbegin(), digits.rend());
        string dp[n+1][3];
        digits.insert(digits.begin(),0);
        dp[0][0] = ""; dp[0][1] = "#"; dp[0][2] = "#"; // # 代表不合法的 不會有 沒字符串 組成餘數1 2狀況
        for(int i = 1; i <= n; i++){
            int k = digits[i]%3;
            for(int j = 0; j < 3; j++){
                //先比較長度 如果相同優先選前者 因為他的數字較大
                if(dp[i-1][j] == "#"  && dp[i-1][(j-k+3)%3] ==  "#"){
                    dp[i][j] = "#";
                }
                else if(dp[i-1][j] == "#"){
                    dp[i][j] = dp[i-1][(j-k+3)%3] + to_string(digits[i]);
                }
                else if(dp[i-1][(j-k+3)%3] == "#"){
                     dp[i][j] = dp[i-1][j];
                }
                else if(dp[i-1][j].size() >= dp[i-1][(j-k+3)%3].size() + 1){
                    dp[i][j] = dp[i-1][j];
                }
                else dp[i][j] = dp[i-1][(j-k+3)%3] + to_string(digits[i]);
            }
        }
        string str = dp[n][0];
        if(str[0] == '0'){
          return "0";
        }
        else
          return dp[n][0];

    }
};

// 優化 不用帶著每次走到的冗長紀錄往後走 另開兩個數組紀錄走的時候選取的對象以及他上一個要對到哪 TC:O(nlgn + 3*n) SC:O(3*n)
class Solution {
public:
    string largestMultipleOfThree(vector<int>& digits) {
        int n = digits.size();
        sort(digits.rbegin(), digits.rend());
        int dp[n+1][3];//直接計算長度
        bool pick[n+1][3];
        int prev[n+1][3];//為了重構dp遍歷的答案
        digits.insert(digits.begin(),0);
        dp[0][0] = 0; dp[0][1] = INT_MIN; dp[0][2] = INT_MIN;
        //dp[0][0] = ""; dp[0][1] = "#"; dp[0][2] = "#"; // # 代表不合法的 不會有 沒字符串 組成餘數1 2狀況
        for(int i = 1; i <= n; i++){
            int k = digits[i]%3;
            for(int j = 0; j < 3; j++){
                if(dp[i-1][j] >= dp[i-1][(j-k+3)%3] + 1){
                    dp[i][j] = dp[i-1][j];
                    pick[i][j] = false;
                    prev[i][j] = j;
                }
                else{
                    dp[i][j] = dp[i-1][(j-k+3)%3] + 1;
                    pick[i][j] = true;
                    prev[i][j] = (j-k+3)%3;
                }
            }
        }

        string res = "";
        int j = 0; // dp[n][0]
        //重構dp答案
        for(int i = n; i >= 1; i--){
            if(pick[i][j]){
                res += '0' + digits[i];
            }
            j = prev[i][j];
        }
        reverse(res.begin(), res.end());
        if(res[0] == '0') return "0";
        else return res;
        

    }
};

/*
給你一堆digit 讓你構造最大的三的倍數
先挑數字長度  再讓數字大
dp[i][j] 被3除餘j的最大數字為多少[i]: 截止到i為止 [j]數字餘數
1. do not picked digits[i]
dp[i][j] = dp[i-1][j]
2. picked digits[i]
k為目前digits[i]%3
dp[i][j] = dp[i-1][j-k] + digits[i]
dp[i][j] = better(dp[i-1][j], dp[i-1][j-k] + digits[i]);
return dp[n][0];

優化：
to reconstruct the string, we need to know two things 
1. for the i-th digit, did we pick it in the final solution
2.  what is the previous state for (i,j)-> (i-1, ?)

*/
