/*
2801. Count Stepping Numbers in Range
*/

// 數位DP TC:O(n*11*2) SC:O(n*11
class Solution {
    using LL = long long;
    LL MOD = 1e9 + 7;
public:
    int countSteppingNumbers(string low, string high) {
        auto check = [&](string& s) {
            int n = s.size();
            if(n == 1) return 1;
            for(int i = 1; i < n; i++) {
                int prev = (s[i-1] - '0');
                int cur = (s[i] - '0');
                if(abs(cur - prev) != 1) return 0; 
            }

            return 1;
        };
        function<LL(string&)> countNumber = [&](string& s) -> LL {
            int m = s.size();
            vector<vector<LL>> memo(m, vector<LL>(11,-1)); // -1 -> 0, 0 -> 1...
            function<LL(int, bool, bool, int)> dfs = [&](int i, bool isLimit, bool isNum, int prev) -> LL {
                if(i == m) return isNum;
                if(!isLimit && isNum && memo[i][prev+1] != -1) return memo[i][prev+1];
                LL res = 0;
                if(!isNum) res = dfs(i+1, false, false, prev);
                
                if(prev == -1) {
                    int up = isLimit ? s[i]-'0' : 9;
                    for(int j = 1; j <= up; j++) {
                        res = (res + dfs(i+1, isLimit && j == up, true, j)) % MOD;
                    }
                }
                else {
                    int lower = prev == 0 ? -1 : prev - 1;
                    int upper = prev == 9 ? -1 : prev + 1;
                    if (!(lower == -1 || (isLimit && lower > s[i] - '0'))) res = (res + dfs(i+1, isLimit && lower == s[i] - '0', true, lower)) % MOD;
                    if (!(upper == -1 || (isLimit && upper > s[i] - '0'))) res = (res + dfs(i+1, isLimit && upper == s[i] - '0', true, upper)) % MOD;
                }

                if(!isLimit && isNum) memo[i][prev+1] = res;
                return res;
            };

            return dfs(0, true, false, -1);
        };

        return (((countNumber(high) - countNumber(low)) % MOD + MOD) % MOD + check(low)) % MOD;
    }
};

/*
區間技巧 + 希望相鄰數字差一
*/

//  Math TC:O(n*10^2) SC:O(n*10^2)
class Solution {
    using LL = long long;
    LL M = 1e9 + 7;
public:
    int countSteppingNumbers(string low, string high) {
      
        return ((helper(high) - helper(low)+M)%M + check(low)) % M;
    }

    LL helper(string& s){
        LL res = 0;
        int memo[105][10][2];
        memset(memo, -1, sizeof(memo));
        int n = s.size();

        for(int len = 1; len < n; len++){
            for(int num = 1; num <= 9; num++){
                res = (res + DFS(len-1, s, num, false, memo)) % M;
            }
        }

        int D = s[0]-'0';
        for(int cur = 1; cur < D; cur++){
            res = (res + DFS(n-1, s, cur, false, memo)) % M;
        }
        res = (res + DFS(n-1, s, D, true, memo)) % M;
        
        return res;
    }

    LL DFS(int len, string& s, int cur, bool same, int memo[105][10][2]){
        int n = s.size();
        
        if(len == 0) return 1;

        if(memo[len][cur][same] != -1) return memo[len][cur][same];

        LL res = 0;
        
        if(same == false){
            int prev = cur;
            if(prev+1 <= 9){
                res = (res + DFS(len-1, s, prev+1, false, memo)) % M;
            }
            if(prev-1 >= 0){
                res = (res + DFS(len-1, s, prev-1, false, memo)) % M;
            }
        }
        //貼合狀態 
        else if(same == true){
            int D = s[n-len] - '0';
            int prev = cur;
            if(prev+1 < D){
                res = (res + DFS(len-1, s, prev+1, false, memo)) % M;
            }
            else if(prev+1 == D){
                res = (res + DFS(len-1, s, prev+1, true, memo)) % M;
            }

            if(prev-1 < D && prev-1 >= 0){
                res = (res + DFS(len-1, s, prev-1, false, memo)) % M;
            }
            else if(prev-1 == D){
                res = (res + DFS(len-1, s, prev-1, true, memo)) % M;
            }
        }

        memo[len][cur][same] = res;
        
        return res;
    }

    bool check(string& low){
        for(int i = 1; i < low.size(); i++){
            if(abs(low[i] - low[i-1]) != 1) return false;
        }

        return true;
    }
};


/*
給你一段區間 low ~ high
找出此段區間所有 stepping number 就是每個數字abs diff = 1

1. 如果目前limit 頭是1 那我就不得不貼合他往下走 
2. 如果不是的話 我可以先減一 不貼合他往下走

ex : 123 
     0 -> 1 or 0 -> 1的話 我必須是0 or 2 , 0的話我是罪後一位9種可能都可以 前面都沒有可能
     1 -> 0 or 2 -> 0的話 只剩1 , 2的話 1 or 3 
0 x x x 
  9 8 9 or 7 -> 
  8 -> 9 or 7 -> 8 or (8 or 6)
  7 

100
10
*/
