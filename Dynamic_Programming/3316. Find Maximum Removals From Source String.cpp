/*
3316. Find Maximum Removals From Source String
*/

// Recursion LCS + 選or 不選 TC:O(m*n) SC:O(m*n)
class Solution {
    unordered_set<int> set;
    string source;
    string pattern;
    vector<int> targetIndices;
    vector<vector<int>> memo;
public:
    int maxRemovals(string source, string pattern, vector<int>& targetIndices) {
        // LCS + 選 or 不選
        int m = source.size();
        int n = pattern.size();
        this -> source = source;
        this -> pattern = pattern;
        this -> targetIndices = targetIndices;
        memo.resize(m+1, vector<int> (n+1,-1));

        for(auto &x : targetIndices) {
            set.insert(x);
        }

        return DFS(m-1, n-1);
    }
    int DFS(int i, int j){
        if(i < j) return INT_MIN;
        if(i < 0) return 0;

        if(memo[i][j+1] != -1) return memo[i][j+1];

        int res = DFS(i-1, j) + set.count(i);
        if(j >= 0 && source[i] == pattern[j]) {
            res = max(res, DFS(i-1,j-1));
        }

        memo[i][j+1] = res;
        return res;
    }
};


// Iterative TC:O(m*n) SC:O(m*n)
class Solution {
public:
    int maxRemovals(string source, string pattern, vector<int>& targetIndices) {
        unordered_set<int> set(targetIndices.begin(), targetIndices.end());
        int m = source.size();
        int n = pattern.size();
        vector<vector<int>> dp(m+1, vector<int>(n+1, INT_MIN/2));

        dp[0][0] = 0;
        for(int i = 0; i < m; i++) {
            dp[i+1][0] = dp[i][0] + set.count(i);
            for(int j = 0; j < n; j++) {
                dp[i+1][j+1] = dp[i][j+1] + set.count(i);
                if(source[i] == pattern[j]) {
                    dp[i+1][j+1] = max(dp[i+1][j+1], dp[i][j]);
                }
            }
        }

        return dp[m][n];
    }
};


// Iterative + 空間優化 + Two pointer TC:O(m*n) SC:O(n)
class Solution {
public:
    int maxRemovals(string source, string pattern, vector<int>& targetIndices) {
        int m = pattern.length();
        vector<int> f(m + 1, INT_MIN);
        f[0] = 0;
        int k = 0;
        for (int i = 0; i < source.length(); i++) {
            if (k < targetIndices.size() && targetIndices[k] < i) {
                k++;
            }
            int is_del = k < targetIndices.size() && targetIndices[k] == i;
            for (int j = min(i, m - 1); j >= 0; j--) {
                f[j + 1] += is_del;
                if (source[i] == pattern[j]) {
                    f[j + 1] = max(f[j + 1], f[j]);
                }
            }
            f[0] += is_del;
        }
        return f[m];
    }
};
