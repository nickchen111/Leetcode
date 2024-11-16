/*
2376. Count Special Integers
*/

// DP TC:O(10*1024*n) SC:O(n*1024)
class Solution {
public:
    int countSpecialNumbers(int n) {
        string s = to_string(n);
        int m = s.size();
        vector<vector<int>> memo(m, vector<int>(1<<10, -1));
        function<int(int i, int mask, bool isLimit, bool isNum)> dfs = [&](int i, int mask, bool isLimit, bool isNum) -> int {
            if(i == m) return isNum;
            if(memo[i][mask] != -1 && !isLimit && isNum) return memo[i][mask];
            int res = 0;
            if(!isNum) res = dfs(i+1, mask, false, false);
            int up = isLimit ? s[i]-'0' : 9;
            for(int j = 1 - (isNum); j <= up; j++) {
                if((mask >> j) & 1) continue;
                res = res + dfs(i+1, mask | 1 << j, isLimit && j == up, true);
            }

            if(!isLimit && isNum) memo[i][mask] = res;
            return res;
        };
        
        return dfs(0, 0, true, false);
    }
};


// Math + Recursion O(10*n) SC:O(n)
class Solution {
    int res = 0;
public:
    int countSpecialNumbers(int N) {
        string str = to_string(N);
        int n = str.size();
        for(int len = 1; len <= n-1; len++){
            res += A(10,len) - A(9,len-1); // 去掉0開頭的狀況
        }

        vector<bool> visited(10);
        DFS(str, 0, visited);

        return res;
    }
    // m代表還可以選擇的數字數目 k代表要填的空格數量
    int A(int m, int k){

        int count = 1;
        for(int i = 0; i < k; i++){
            count *= (m-i);
        }

        return count;
    }
    void DFS(string&str, int cur, vector<bool>& visited){
        if(cur == str.size()){
            res += 1;
            return;
        }

        int n = str.size();
        for(int d = 0; d <= 9; d++){
            if(cur == 0 && d == 0) continue;
            if(visited[d]) continue;
            if(d < str[cur]-'0'){
                res += A(10-cur-1,n-cur-1);
            }
            else if(d == str[cur]-'0'){
                visited[d] = 1;
                DFS(str, cur+1, visited);
                visited[d] = 0;
            }
        }
    }
};

/*
所有數字都不相同 再給定的n範圍內 有多少種符合的數字
1 <= n <= 2 * 10^9
此題與1012 357類似
此題你會先想說如果數字數目小於給定上限
那麼就是隨意排摟 例如可隨意排n個那就是 n*(n-1)*(n-2)...1
如果是相同長度的話:
前面的數字不能為0 然後一個一個的去試如果小於上限的數字 那麼後面的數字都放飛自我 但如果剛好等於當前數字 那後面的數字不一定 需要在DFS
*/
