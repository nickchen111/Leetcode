/*
943. Find the Shortest Superstring
*/

// TC:O(2^n * n * n + (n*n*(m+m))) m 為字串平均長度 SC:O(m*n + n*n + (1<<n)*n)
class Solution {
public:
    string shortestSuperstring(vector<string>& words) {
        int n = words.size();

        auto preprocessor = [](vector<string>& str) {
            int m = str.size();
            vector<vector<int>> res(m);
            for(int t = 0; t < m; t++) {
                string s = str[t];
                int n = s.size();
                vector<int> dp(n);
                for(int i = 1; i < n; i++) {
                    int j = dp[i-1];
                    while(j > 0 && s[i] != s[j]) {
                        j = dp[j-1];
                    }
                    dp[i] = j + (s[i] == s[j]);
                }
                res[t] = dp;
            }

            return res;
        };

        vector<vector<int>> lcs = preprocessor(words);

        auto kmp = [&](string& s, string& t, int idx) -> int{
            int n = s.size();
            vector<int> lsp = lcs[idx];
            vector<int> dp(n);
            dp[0] = (s[0] == t[0]);
            for(int i = 1; i < n; i++){
                int j = dp[i-1];
                while(j > 0 && s[i] != t[j]) j = lsp[j-1];
                dp[i] = j + (s[i] == t[j]);
            }

            return dp[n-1];
        };

        vector<vector<int>> dist(n,vector<int>(n)); // 頭搭配尾巴

        for(int l = 0; l < n; l++) {
            for(int r = 0;r < n; r++) {
                //前綴是你的後綴的最長長度
                if(l == r) continue;
                int len = kmp(words[l], words[r], r);
                dist[l][r] = ((int) words[r].size() - len);
            }
        }
        
        // 狀態壓縮dp 目前頭 尾 state 可以達到的最短長度 111 = 8
        vector<vector<int>> dp((1<<n), vector<int>(n, INT_MAX/2));
        for(int i = 0; i < n; i++) {
            dp[1<<i][i] = (int)words[i].size();
        }

        vector<vector<int>> record((1<<n), vector<int>(n, -1));
        for(int state = 1; state < (1<<n); state++) {
            for(int i = 0; i < n; i++) {
                // 當前有這點
                if((state >> i) & 1) {
                    // state_prev = state - i, 然後遍歷所有之前的點當尾巴
                    int state_prev = state ^ (1<<i);
                    for(int j = 0; j < n; j++) {
                        if((state_prev >> j) & 1) {
                            if(dp[state][i] > dp[state_prev][j] + dist[j][i]) {
                                dp[state][i] = dp[state_prev][j] + dist[j][i];
                                record[state][i] = j;
                            }
                        }
                    }
                }
            }
        }

        int minLen = INT_MAX;
        int last = 0;
        for(int i = 0; i < n; i++) {
            if(minLen > dp[(1<<n)-1][i]) {
                minLen = dp[(1<<n)-1][i];
                last = i;
            }
        }
        int curState = (1 << n) -1;
        string res;
        // len(str) - 當前長度 - 上一次的長度
        while(record[curState][last] != -1) {
            int newState = curState ^ (1 << last);
            int newLast = record[curState][last];
           
            int prevLen = dp[newState][newLast];
            int curLen = dp[curState][last];
            // cout << curLen << ' ' << prevLen << endl;
            // x x x x x  lenDiff = 3
            res = words[last].substr(words[last].size() - (curLen-prevLen)) + res;
            
            last = newLast;
            curState = newState;
        }
        res = words[last] + res;

        return res;
    }
};

/*
該如何把所有字串排出一個最佳的順序組成總字串去讓所有字串都是最後字串的substring
字串之間可能會有前後綴相合這種拿來組合就可以盡量縮短字串長度
所以12*11*10... -> 12*11*10*9*8*7*6*5*4*3*2 = 4*10^8
所以字串其實可以拆解成兩個資訊: 前+後 都是誰? 這種狀態 但是我們還需要用一個變量去表示最後是誰?
我就可以判斷說 ex : index 0 與 index 1 相配出來的共同長度為多少? m+n - 共同長度 然後更新後面的index

狀態壓縮dp 目前尾 state 可以達到的最短長度
但還有個問題是如何重構方案 目前想到的是重構選擇vector 
*/
