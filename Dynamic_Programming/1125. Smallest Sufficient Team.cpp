/*
1125. Smallest Sufficient Team
*/

// 2024.12.30 新增輸出具體方案的雙遞歸  TC:O(T + m * 2^n) SC:O(m * 2^n)
class Solution {
    using LL = long long;
public:
    vector<int> smallestSufficientTeam(vector<string>& req_skills, vector<vector<string>>& people) {
        int n = req_skills.size();
        int m = people.size();
        unordered_map<string, int> map;
        for(int i = 0; i < n; i++) map[req_skills[i]] = i;
        vector<int> arr(m);
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < people[i].size(); j++) {
                arr[i] |= (1 << map[people[i][j]]);
            }
        }
        // 輸出具體方案雙遞迴寫法
        vector<vector<LL>> memo((1 << n), vector<LL>(m,-1));
        auto dfs = [&](auto &&dfs, int mask, int j) -> int {
            if(mask == (1 << n) - 1) return 0;
            if(j == m) return m;
            if(memo[mask][j] != -1) return memo[mask][j];
            int ret = min(dfs(dfs, mask, j + 1), dfs(dfs, mask | arr[j], j + 1) + 1);
            return memo[mask][j] = ret;
        };

        vector<int> res;
        auto print_ans = [&](auto &&print_ans, int mask, int j) -> void {
            if(mask == (1 << n) - 1) return;
            if(j == m) return;
            int ret1 = dfs(dfs, mask, j + 1);
            int ret2 = dfs(dfs, mask | arr[j], j + 1) + 1;
            if(ret1 < ret2) {
                print_ans(print_ans, mask, j + 1);
            }
            else {
                res.push_back(j);
                print_ans(print_ans, mask | arr[j], j + 1);
            }
        };
        print_ans(print_ans, 0, 0);
        return res;
        /*
        遞歸 TC:O(T + m * 2^n) SC:O(m * 2^n)
        vector<vector<LL>> memo((1 << n), vector<LL>(m,-1));
        auto dfs = [&](auto &&dfs, int mask, int j) -> LL {
            if(mask == (1 << n) - 1) return 0;
            if(j == m) return (1LL << m) - 1LL;
            if(memo[mask][j] != -1) return memo[mask][j];
            LL ret1 = dfs(dfs, mask, j + 1);
            LL ret2 = dfs(dfs, mask | arr[j], j + 1) | (1LL << j);
            
            return memo[mask][j] = __builtin_popcountll(ret1) < __builtin_popcountll(ret2) ? ret1 : ret2;
        };
        LL ret = dfs(dfs, 0, 0);
        vector<int> res;
        
        for(int i = 0; i < m; i++) {
            if((ret >> i) & 1) res.push_back(i);
        }

        return res;
        */
    }
};

// TC:O(T + n*2^m) T為字串加總長度 SC:O(n*2^m)
class Solution {
public:
    vector<int> smallestSufficientTeam(vector<string>& req_skills, vector<vector<string>>& people) {
        int m = req_skills.size();
        unordered_map<string, int> map;
        for(int i = 0; i < m; i++) {
            map[req_skills[i]] = i;
        }
        int n = people.size();
        vector<int> peopleState(n);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < people[i].size(); j++) {
                peopleState[i] |= (1 << map[people[i][j]]);
            }
        }

        vector<vector<long long>> memo(n, vector<long long>(1 << m, -1));

        function<long long(int i, int j)> DFS = [&](int i, int j) -> long long {
            if (j == 0) return 0;
            if (i < 0) return LLONG_MAX/2;
            if (memo[i][j] != -1) return memo[i][j];
            auto r1 = DFS(i - 1, j); 
            auto r2 = DFS(i - 1, j & ~peopleState[i]) | (1LL << i); 
            return memo[i][j] = __builtin_popcountll(r1) < __builtin_popcountll(r2) ? r1 : r2;
        };

        auto res = DFS(n-1, (1 << m) - 1);

        vector<int> ret;
        for(int i = 0; i < n; i++) {
            if(((res >> i) & 1)) ret.push_back(i);
        }

        return ret;
    }
};
