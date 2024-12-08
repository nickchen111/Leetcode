/*
1947. Maximum Compatibility Score Sum
*/

// 狀壓DP TC:O(n * 2^n) SC:O(2^n)
class Solution {
public:
    int maxCompatibilitySum(vector<vector<int>>& students, vector<vector<int>>& mentors) {
        int n = students.size();
        vector<int> memo((1<<n), -1);
        auto dfs = [&](auto &&dfs, int status) -> int {
            if(status == (1 << n) - 1) return 0;
            if(memo[status] != -1) return memo[status];
            int idx = __builtin_popcount(status);
            int ret = 0;
            for(int i = 0; i < n; i++) {
                if(((status >> i) & 1) == 0) {
                    int cnt = 0;
                    for(int j = 0; j < students[i].size(); j++) {
                        if(students[i][j] == mentors[idx][j]) cnt += 1;
                    }
                    ret = max(ret, dfs(dfs, status | (1<<i)) + cnt);
                }
            }
            return memo[status] = ret;
        };
    
        return dfs(dfs, 0);
    }
};

// Backtrack: TC:O(n!) SC:O(n!)
class Solution {
public:
    int maxCompatibilitySum(vector<vector<int>>& students, vector<vector<int>>& mentors) {
        int n = students.size();
        int res = 0;
        auto back = [&](auto && back, int status, int idx, int total) -> void {
            if(idx == n) {
                res = max(res, total);
                return;
            }
            for(int i = 0; i < n; i++) {
                if(((status >> i) & 1) == 0) {
                    int cnt = 0;
                    for(int j = 0; j < students[i].size(); j++) {
                        if(students[i][j] == mentors[idx][j]) {
                            cnt += 1;
                        }
                    }
                    back(back, (status | (1<<i)), idx+1, total + cnt);
                }
            }
        };

        back(back, 0, 0, 0);
        return res;
    }
};
