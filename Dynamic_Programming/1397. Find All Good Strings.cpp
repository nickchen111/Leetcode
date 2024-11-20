/*
1397. Find All Good Strings
*/


// TC:O(k + (n+k) + max(m,n) + m*26 + n*26 + m*k*26*k + n*k*26*k) SC:O(m*k + n*k + max(m,n) + k + m)
class Solution {
    using LL = long long;
    LL MOD = 1e9 + 7;
public:
    int findGoodStrings(int n, string s1, string s2, string evil) {
        int k = evil.size();
        function<vector<int>(string&)> preprocessor = [&](string& evil) -> vector<int> {
            int m = evil.size();
            vector<int> dp(m);
            for(int i = 1; i < m; i++) {
                int j = dp[i-1];
                while(j > 0 && evil[j] != evil[i]) {
                    j = dp[j-1];
                }
                dp[i] = j + (evil[j] == evil[i]);
            }
            return dp;
        };
    
        vector<int> lsp = preprocessor(evil);
        vector<LL> power(501);
        power[0] = 1;
        for(int i = 1; i <= max((int)s1.size(), (int)s2.size()); i++) {
            power[i] = (power[i-1] * 26) % MOD;
        }
        auto kmp = [&](string& s) -> LL {
            int m = s.size();
            vector<int> dp(m);
            dp[0] = (s[0] == evil[0] ? 1 : 0);
            for(int i = 1; i < m; i++) {
                int j = dp[i-1];
                while(j > 0 && evil[j] != s[i]) {
                    j = lsp[j-1];
                }
                dp[i] = j + (evil[j] == s[i]);
                if(dp[i] == k) return 0LL;
            }

            return 1LL;
        };
        function<LL(string&)> countTotalPossible = [&](string& s) -> LL {
            int m = s.size();
            function<LL(int, bool, bool)> dfs = [&](int i, bool isLimit, bool isString) -> LL {
                if(i == m) return isString;
                LL res = 0;
                if(!isString) res = dfs(i+1,false, false);
                int up = isLimit ? s[i] : 'z';
                if(isLimit) {
                    for(char ch = 'a'; ch <= up; ch++) {
                        // x x x x x x
                        res = (res + dfs(i + 1, isLimit && ch == up, true)) % MOD;
                    }
                } 
                else {
                    res = (res + power[m-i]) % MOD;
                }
                
                return res;
            };

            return dfs(0, true, false);
        };
        function<LL(string&)> countBadString = [&](string& s) -> LL{
            int m = s.size();
            vector<vector<LL>> memo(m, vector<LL>(k+1,-1));
            function<LL(int, bool, bool, int)> dfs = [&](int i, bool isLimit, bool isString, int idx) -> LL {
                if(m < k) return 0;
                if(i == m) return isString && idx == k;
                if(!isLimit && isString && memo[i][idx] != -1) return memo[i][idx];
                LL res = 0;
                if(!isString) res = dfs(i+1, false, false, idx);
                char up = isLimit ? s[i] : 'z';
                if(idx == k) {
                    // for(char ch = 'a'; ch <= up; ch++) {
                    //     res = (res + dfs(i+1, isLimit && ch == up, true, idx)) % MOD;
                    // }
                    if(!isLimit) {
                        res = (res + power[m-i]) % MOD;
                    }
                    else {
                        res = (res + (LL)(s[i]-'a') * power[m-i-1]) % MOD;
                        res = (res + dfs(i+1, isLimit, true, idx)) % MOD;
                    }
                }
                else {
                    for(char ch = 'a'; ch <= up; ch++) {
                        if(evil[idx] == ch) {
                            res = (res + dfs(i+1, isLimit && ch == up, true, idx+1)) % MOD;
                        }
                        else {
                            int nextIdx = idx;
                            while(nextIdx > 0 && evil[nextIdx] != ch) {
                                nextIdx = lsp[nextIdx-1];
                            }
                            res = (res + dfs(i+1, isLimit && ch == up, true, evil[nextIdx] == ch ? nextIdx+1 : 0)) % MOD;
                        }
                    }
                }

                if(!isLimit && isString) memo[i][idx] = res;
                return res;
            };

            return dfs(0, true, false, 0);
        };

        LL num1 = ((countTotalPossible(s1) - countBadString(s1)) % MOD + MOD) % MOD;
        LL num2 = ((countTotalPossible(s2) - countBadString(s2)) % MOD + MOD) % MOD;
        return (((num2 - num1) % MOD + MOD) % MOD + + kmp(s1)) % MOD;

    }
};

/*
就是介於兩個字串中並且沒有evil作為substring在裡頭
可以用正難則反嗎 一定要包含此substring的有多少種
字串長度最多到500 可以用快速冪去做26的次方
但不確定是否可以先取餘後再做 所以會不取先做
aa
a : a
x -> 26 => 26 + 1

*/
