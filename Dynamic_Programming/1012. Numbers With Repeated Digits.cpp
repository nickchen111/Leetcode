/*
1012. Numbers With Repeated Digits
*/


// 正難則反 TC:O(n*mask*10) SC:O(n*mask)
class Solution {
public:
    int numDupDigitsAtMostN(int n) {
        string s = to_string(n);
        int m = s.size();
        vector<vector<vector<int>>> memo(m, vector<vector<int>>(1 << 10, vector<int>(2,-1)));
        // vector<vector<int>> memo(m, vector<int>(1 << 10, -1));
        function<int(int i, int mask, bool repeat, bool isLimit, bool isNum)> dfs = [&](int i, int mask, bool repeat, bool isLimit, bool isNum) -> int {
            if (i == m) return isNum && repeat;
            if (!isLimit && isNum && memo[i][mask][repeat] != -1) return memo[i][mask][repeat];
            int res = 0;
            if (!isNum) res = dfs(i + 1, mask, false, false, false);
            int up = isLimit ? s[i] - '0' : 9;
            for (int j = 1 - (isNum); j <= up; j++) {
                if((mask >> j) & 1) 
                    res = res + dfs(i+1, mask, true, isLimit && j == up, true);
                else 
                    res = res + dfs(i+1, mask | (1 << j), repeat, isLimit && j == up, true);
            }

            if(!isLimit && isNum) memo[i][mask][repeat] = res;
            return res;
        };

        return dfs(0, 0, false, true, false);
    }
};


// TC:O(n*mask*10*2) SC:O(n*mask)
class Solution {
public:
    int numDupDigitsAtMostN(int n) {
        string s = to_string(n);
        int m = s.size();
        vector<vector<vector<int>>> memo(m, vector<vector<int>>(1 << 10, vector<int>(2,-1)));
        // vector<vector<int>> memo(m, vector<int>(1 << 10, -1));
        function<int(int i, int mask, bool repeat, bool isLimit, bool isNum)> dfs = [&](int i, int mask, bool repeat, bool isLimit, bool isNum) -> int {
            if (i == m) return isNum && repeat;
            if (!isLimit && isNum && memo[i][mask][repeat] != -1) return memo[i][mask][repeat];
            int res = 0;
            if (!isNum) res = dfs(i + 1, mask, false, false, false);
            int up = isLimit ? s[i] - '0' : 9;
            for (int j = 1 - (isNum); j <= up; j++) {
                if((mask >> j) & 1) 
                    res = res + dfs(i+1, mask, true, isLimit && j == up, true);
                else 
                    res = res + dfs(i+1, mask | (1 << j), repeat, isLimit && j == up, true);
            }

            if(!isLimit && isNum) memo[i][mask][repeat] = res;
            return res;
        };

        return dfs(0, 0, false, true, false);
    }
};

// Math TC:O(n*10) SC:O(1)
class Solution {
    int res = 0;
public:
    int numDupDigitsAtMostN(int N) {
        string str = to_string(N);
        int n = str.size();
        for(int len = 1; len <= n-1; len++){
            res += A(10,len) - A(9, len-1);
        }

        vector<bool> visited(10);
        DFS(str, 0, visited);

        return N - res;
    }
    void DFS(string& s, int i, vector<bool>& visited){
        if(i == s.size()){
            res += 1;
            return;
        }
        int n = s.size();
        for(int d = 0; d <= 9; d++){
            if(i == 0 && d == 0) continue;
            if(visited[d]) continue;
            if(d < s[i]-'0'){
                res += A(10-i-1, n-i-1);
            }
            else if(d == s[i]-'0') {
                visited[d] = 1;
                DFS(s, i+1, visited);
            }
        }
    }
    int A(int m, int n){
        int count = 1;
        for(int i = 0; i < n; i++){
            count *= (m-i);
        }

        return count;
    }
};

/*
1 ~ n 之間
我會把n轉成字串好進行大小比對
再來是判斷當前的字串是否已經有重複的字元狀況的bool數值
再來是需要一個limit 判斷是否逼近極限值
還需要一個數值代表是否是題目要求的正數
*/
