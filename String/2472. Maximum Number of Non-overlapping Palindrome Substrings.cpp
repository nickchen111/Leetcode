/*
2472. Maximum Number of Non-overlapping Palindrome Substrings
*/

// Manacher TC:O(n) SC:O(n)
class Solution {
    vector<int> p;
    string ss;
public:
    int maxPalindromes(string s, int k) {
        int n = s.size();
        int next = 0;
        int res = 0;
        ss = "#";
        for(auto &ch : s) {
            ss += ch;
            ss += "#";
        }

        p.resize(2*n+1);

        while((next = (find(next,k))) != -1) {
            res += 1;
        }

        return res;
    }
    int find(int l, int k) {
        for(int i = l, r = l ,c = l, len; i < p.size(); i++) {
            len = r > i ? min(p[2*c-i], r - i) : 1;
            while(i + len < p.size() && i - len >= l && ss[i+len] == ss[i-len]) {
                if(++len > k) {
                    return i + k + (ss[i+k] == '#' ? 0 : 1);
                } 
            }
            if(i + len > r) {
                r = i + len;
                c = i;
            }
            p[i] = len;
        }

        return -1;
    }
};


// DP TC:O(n^2) SC:O(n^2)
class Solution {
public:
    int maxPalindromes(string s, int k) {
        int n = s.size();
        // DP
        vector<vector<bool>> check(n, vector<bool>(n));
        for(int i = 0; i < n; i ++) {
            check[i][i] = 1;
        }
        for(int i = 1; i < n; i ++) {
            if(s[i] == s[i-1]) {
                check[i-1][i] = 1;
            }
        }
        for(int len = 3; len <= n; len++) {
            for(int i = 0; i + len - 1 < n; i++) {
                int j = i + len - 1;
                if(s[i] == s[j] && check[i+1][j-1]) {
                    check[i][j] = 1;
                }
            }
        }
        
        vector<int> dp(n);
        dp[k-1] = check[0][k-1];
        for(int i = k; i < n; i++) {
            dp[i] = dp[i-1];
            for(int j = i-k+1; j >= 0; j--) {
                dp[i] = max(dp[i], (j-1 >= 0 ? dp[j-1] : 0) + (check[j][i]));
            }
        }

        return dp[n-1];
    }
};
