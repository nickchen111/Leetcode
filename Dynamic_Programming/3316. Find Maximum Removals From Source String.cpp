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
