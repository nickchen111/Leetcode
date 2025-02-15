// MEMO TC:O(n * m * n) m = 字串長度 max:7 SC:O(m * n)
class Solution {
public:
    int punishmentNumber(int n) {
        int ans = 0;
        
        for(int i = 1; i <= n; i++) {
            int square = i * i;
            string s = to_string(square); // 最大 7 位數
            int m = s.size();
            vector<vector<int>> memo(m, vector<int>(i+1, -1));
            auto dfs = [&](auto &&dfs, int i, int target) -> bool {
                if (i == m) return target == 0;
                if(target < 0) return false;
                if(memo[i][target] != -1) return memo[i][target];
                int cur = 0;
                for (int j = i; j < m; j++) {
                    cur = cur * 10 + (s[j] - '0');
                    if (cur > target) break;
                    if (dfs(dfs, j + 1, target - cur)) 
                        return memo[i][target] = true;
                }
                return memo[i][target] = false;
            };
            
            if (dfs(dfs, 0, i)) {
                ans += i * i;
            }
        }
        return ans;
    }
};

// Backtrack TC:O(n * 2^m) m = 字串長度 max:7 dfs(i,j) j的變化可被剪枝以及他是跳躍式減少而忽略 可當作常數 SC:O(m * n)
class Solution {
public:
    int punishmentNumber(int n) {
        int ans = 0;
        
        for(int i = 1; i <= n; i++) {
            int square = i * i;
            string s = to_string(square); // 最大 7 位數
            int m = s.size();
            // vector<vector<int>> memo(m, vector<int>(i+1, -1));
            auto dfs = [&](auto &&dfs, int i, int target) -> bool {
                if (i == m) return target == 0;
                if(target < 0) return false;
                // if(memo[i][target] != -1) return memo[i][target];
                int cur = 0;
                for (int j = i; j < m; j++) {
                    cur = cur * 10 + (s[j] - '0');
                    if (cur > target) break;
                    if (dfs(dfs, j + 1, target - cur)) 
                        return true;
                }
                return false;
            };
            
            if (dfs(dfs, 0, i)) {
                ans += i * i;
            }
        }
        return ans;
    }
};

/*
問說從1-n 中的數字x 每個數字的 ^2 他們可以被拆解後加總為x
^2 最多到10^6 也就是七個數字
*/
