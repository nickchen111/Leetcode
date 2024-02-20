/*
2801. Count Stepping Numbers in Range
*/

// 此類時間複雜度都取決於memo空間有多大 切入點1 : TC:O(105^10^2) SC:O(105^10^2)
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

// 切入點2 將第一項數字的選取工作交給DFS判斷 TC:O(105^10^2^2) SC:O(105^10^2^2)
class Solution {
    using LL = long long;
    LL M = 1e9 + 7;
public:
    int countSteppingNumbers(string low, string high) {
      
        return (helper(high) - helper(low) + check(low)) % M;
    }

    LL helper(string& s){
        LL res = 0;
        int memo[105][10][2][2];
        memset(memo, -1, sizeof(memo));
        int n = s.size();
        for(int ch = 0; ch <= s[0]-'0'; ch++){
            if(ch == 0){
                res += DFS(ch, s, 0, false, false, memo);
            }
            else if(ch < s[0]-'0'){
                res += DFS(ch, s, 0, false, true, memo);
            }
            else if(ch == s[0]-'0') res += DFS(ch, s, 0, true, true, memo);
        }
        
        return res;
    }
    LL DFS(int cur, string& s, int idx, bool same, bool choose, int memo[105][10][2][2]){
        
        if(idx == s.size()-1){
            if(choose == true){
                return 1;
            } 
            else return 0;
        }
        if(memo[idx][cur][same][choose] != -1) return memo[idx][cur][same][choose];

        LL res = 0;
        if(choose == false){
            for(int ch = 0; ch <= 9; ch++){
                if(ch == 0){
                    res += DFS(ch, s, idx+1, false, false, memo);
                }
                else res += DFS(ch, s, idx+1, false, true, memo);
            }
        }

        else if(same == false){
            int prev = cur;
            if(prev+1 <= 9){
                res = (res + DFS(prev+1, s, idx+1, false, true, memo)) % M;
            }
            if(prev-1 >= 0){
                res = (res + DFS(prev-1, s, idx+1, false, true, memo)) % M;
            }
        }
        //貼合狀態 
        else if(same == true){
            int D = s[idx+1] - '0';
            int prev = cur;
            if(prev+1 < D){
                res = (res + DFS(prev+1, s, idx+1, false, true, memo)) % M;
            }
            else if(prev+1 == D){
                res = (res + DFS(prev+1, s, idx+1, true, true, memo)) % M;
            }

            if(prev-1 < D && prev-1 >= 0){
                res = (res + DFS(prev-1, s, idx+1, false, true, memo)) % M;
            }
            else if(prev-1 == D){
                res = (res + DFS(prev-1, s, idx+1, true, true, memo)) % M;
            }
        }

        memo[idx][cur][same][choose] = res;

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
