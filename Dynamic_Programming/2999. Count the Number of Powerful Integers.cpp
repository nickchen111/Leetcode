/*
2999. Count the Number of Powerful Integers
*/

// TC:O(n * limit * 2 * 2) SC:O(n)
class Solution {
    using LL = long long;
public:
    long long numberOfPowerfulInt(long long start, long long finish, int limit, string s) {
        int len = s.size();
        function<LL(LL)> countPowerful = [&](LL n) -> LL{
            string s1 = to_string(n);
            int m = s1.size();
            // vector<vector<vector<LL>>> memo(m, vector<vector<LL>>(2, vector<LL>(2, -1)));
            vector<LL> memo(m, -1);
            function<LL(int, bool, bool)> dfs = [&](int i, bool isLimit, bool isNum) -> LL {
                if(len > m || (len == m && s1 < s)) return 0;
                // x x x x x x x x len = 3
                if(i == m - len) {
                    if(!isLimit ||  s1.substr(i) >= s) {
                        return 1;
                    }
                    return 0;
                }
                if(!isLimit && isNum && memo[i] != -1) return memo[i];
                LL res = 0;
                if(!isNum) res = dfs(i+1, false, false);
                int up = isLimit ? min(limit, s1[i]-'0') : limit;
                for(int j = 1 - isNum; j <= up; j++) {
                    res += dfs(i+1, isLimit && j == (s1[i]-'0'), true);
                }

                if(!isLimit && isNum) memo[i] = res;

                return res;
            };
            return dfs(0, true, false);
        };
       
        return countPowerful(finish) - countPowerful(start-1);
    }
};

// Math 
class Solution {
    using LL = long long;
public:
    long long numberOfPowerfulInt(long long start, long long finish, int limit, string s) {
        return helper(to_string(finish), limit, s) - helper(to_string(start-1), limit, s);
    }

    LL helper(string a, int limit, string s){
        if(a.size() < s.size()) return 0;
        
        return DFS(a, limit, s, 0, true);
    }
    // k代表看到第幾個數字
    LL DFS(string a, int limit, string s, int k, bool isSame){
        if(a.size()-k == s.size()){
            if(!isSame || a.substr(k) >= s){
                return 1;
            }
            else return 0;
        }

        LL res = 0;

        if(isSame){
            for(int i = 0; i <= min(a[k]-'0', limit); i++){
                if(i == a[k]-'0'){
                    res += DFS(a, limit, s, k+1, true);
                }
                else res += DFS(a, limit, s, k+1, false);
            }
        }
        else {
            //代表前面沒有貼合 我現在可以亂選一波
            int d = a.size() - s.size() - k;
            res += pow(limit+1, d);
        }

        return res;

    }
};

/*
此題希望你找出給定區間中 
滿足以下條件的字串總數
1 字串尾數是指定的字串
2.字串其他數字不能超過limit
首先因為他給了上界下界 所以用兩次遞歸的方式去做會比較方便只需考慮一個上界
再來考慮目前recursion的前綴是否貼合給的上限 這樣就分成兩種情況
1. 貼合 那麼我後續走的數字就只能是 min(a[k], limit) 取較小的 
2. 不貼合 那麼我後面的數字其實都可以在limit範圍內任意取 a.size()-s.size()-k個

x x x x x x 
n = 6 k = 3 s = 3
*/

/*
1. 區間範圍內數字
2. 每個數字的限制範圍limit
3. 後綴一定要是string s 這個部分就要看有碰到目前數字狀況下 他是否可以往下走
*/
