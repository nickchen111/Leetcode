/*
1125. Smallest Sufficient Team
*/

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
