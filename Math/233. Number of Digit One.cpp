/*
233. Number of Digit One
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int countDigitOne(int n) {
        long res = 0;
        if(n == 0) return 0;
        string str = to_string(n);
        long N = str.size();
        // 1-index 假裝從他的尾巴開始遍歷上去
        for(int i = 1; i <= N; i++){
            //假設想將它改成1 前面數字讓他變小 後面都可以
            long a = n / (long)pow(10,i);
            res += a * (long)pow(10,i-1);

            // 開始對當下原本數字做判斷
            if(str[N-i]-'0' > 1){
                res += (long)pow(10,i-1);
            }
            else if(str[N-i]-'0' == 1){
                res += n % (long)pow(10,i-1) + 1;
            }
        }


        return res;
    }
};

// DP TC:O(10*n) SC:O(10*n)
class Solution {
public:
    int countDigitOne(int n) {
        string s = to_string(n);
        int m = s.size();
        vector<vector<int>> memo(m, vector<int>(10,-1));
        function<int(int i, bool isLimit, bool isNum, int count)> dfs = [&](int i, bool isLimit, bool isNum, int count) -> int {
            if(i == m) return count;
            if(memo[i][count] != -1 && !isLimit && isNum) return memo[i][count];
            int res = 0;
            if(!isNum) res = dfs(i+1, false, false, 0);
            int up = isLimit ? s[i]-'0' : 9;
            for(int j = 1 -(isNum); j <= up; j++) {
                res = res + dfs(i+1, isLimit && (j == up), true, count + (j == 1));
            }

            if(!isLimit && isNum) memo[i][count] = res;

            return res;
        };

        return dfs(0, true, false, 0);
    }
};

/*
給你一個數字 算出在這個數字以內的數字有多少個1
要將目前的數字設為1:
2 3 6 4 5 3
    x
0~22  0~999
開始判斷目前數字為何
23前面一串不變 當下數字如果是 0 那就不能加東西 如果是1 可以加入453個答案 如果大於1可以加入 10^3

*/
