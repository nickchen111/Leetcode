/*
788. Rotated Digits
*/

// TC:O(10*n) SC:O(n)
class Solution {
public:
    int rotatedDigits(int n) {
        string s = to_string(n);
        int m = s.size();
        vector<int> memo(m,-1);
        vector<int> inValid(10);
        vector<int> check(10);
        check[2] = 1, check[5] = 1, check[6] = 1, check[9] = 1;
        inValid[3] = 1, inValid[4] = 1, inValid[7] = 1;
        function<int(int i, bool isLimit, bool isNum, bool isValid)> dfs = [&](int i, bool isLimit, bool isNum, bool isValid) -> int {
            if(i == m) {
                return (isNum && isValid);
            }
            if(!isLimit && memo[i] != -1 && isNum && isValid) return memo[i];
            int res = 0;
            // 代表是否有數字過了!?
            if(!isNum) {
                res = dfs(i+1, false, false, false);
            }
            int up = isLimit ? s[i]-'0' : 9;
            for(int j = 1-(isNum); j <= up; j++) {
                if(inValid[j]) continue;
                res = res + dfs(i+1, isLimit && j == up, true, isValid || check[j]); 
            }

            if(!isLimit && isNum && isValid) memo[i] = res;
            
            return res;
        };

        return dfs(0, true, false, false);
    }
};


/*
只要有2 or 5 or 6 or 9就會是ok的 
0,1,8 只會變自己
其他數字都不能選 -> 3 4 7 選了就掰
*/
