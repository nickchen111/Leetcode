/*
2843. Count Symmetric Integers
*/

// TC : O(m*maxSum * 10) SC:O(m*maxSum)
class Solution {
public:
    int countSymmetricIntegers(int low, int high) {
        function<int(int)> countInteger = [&](int n) -> int {
            if(n == 0) return 0;
            string s = to_string(n);
            int m = s.size();
            int offset = 20;
            vector<vector<int>> memo(m, vector<int>(41,-1));
            function<int(int, bool, bool, int, int, int)> dfs = [&](int i, bool isLimit, bool isNum, int sum, int len, int target) -> int {
                if(i == m) return isNum && sum == 0;
                if(!isLimit && isNum && memo[i][sum+offset] != -1) return memo[i][sum+offset];
                int res = 0;
                if(!isNum) res = dfs(i+1, false, false, sum, len, target);
                // x x x x x x 
                if(((m-i) % 2) == 0 || len) {
                    int up = isLimit ? s[i]-'0' : 9;
                    int nxtTarget = isNum ? target : m-i;
                    for(int j = 1 - isNum; j <= up; j++) {
                        res += dfs(i+1, isLimit && j == up, true, sum + ((len+1) > nxtTarget/2 ? -j : j), len+1, nxtTarget);
                    }
                }
                if(!isLimit && isNum) memo[i][sum+offset] = res;
                return res;
            };
            return dfs(0, true, false, 0, 0, m);
        };
        
        return countInteger(high) - countInteger(low-1);
    }
};

/*
求一段區間內 左邊數字總和 = 右邊數字總和的數字有多少個
到了某個點總和是多少 這個是可以memo的 
目前長度/2 odd長度強迫下一位 
偶數長度 我們就開始以這一位數的長度當作基準 左邊sum 右邊sum 你目前達到的長度
*/
