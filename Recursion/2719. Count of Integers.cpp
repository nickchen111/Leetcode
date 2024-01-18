/*
2719. Count of Integers
*/

// TC: O(9*n) SC:O(2*25*405 + n)
class Solution {
    using LL = long long;
    LL M = 1e9+7;
public:
    int count(string num1, string num2, int min_sum, int max_sum) {
        
        LL res = (helper(num2, max_sum)+M - helper(num2, min_sum-1)+M)%M - (helper(num1, max_sum)+M - helper(num1, min_sum-1)+M)%M;
        res = (res + M) % M;
        int digitsum = calculate(num1);
        if(digitsum >= min_sum && digitsum <= max_sum){
            res += 1;
            res %= M;
        }

        return res;
    }
    int calculate(string num1){
        int res = 0;
        for(char ch : num1){
            res += ch-'0';
        }
        return res;
    }

    LL helper(string num, int limit){

        vector<vector<vector<int>>> memo(2, vector<vector<int>>(25, vector<int>(405,-1)));
        return DFS(num,limit, 0, 0, true, memo);
    }
    LL DFS(string num, int limit, int cur, int sum, bool same, vector<vector<vector<int>>>& memo){

        if(sum > limit) return 0;
        if(memo[same][cur][sum] != -1) return memo[same][cur][sum];
        if(cur == num.size()) return 1;

        LL res = 0;
        if(!same){
            for(int d = 0; d <= 9; d++){
                res += DFS(num, limit, cur+1, sum+d, false, memo);
                res %= M;
            }
        }
        else {
            for(int d = 0; d <= (num[cur]-'0'); d++){
                if(d < num[cur]-'0'){
                    res += DFS(num, limit, cur+1, sum+d, false, memo);
                    res %= M;
                } 
                else if(d == num[cur]-'0'){
                    res += DFS(num, limit, cur+1, sum+d, true, memo);
                    res %= M;
                } 
            }
        }

        memo[same][cur][sum] = res;

        return res;
    }
};

/*
num1 num2是你能選擇的數字區間
min_sum max_sum 是digit相加的區間限制
157 300000
200 -> 2+0+0
*/
