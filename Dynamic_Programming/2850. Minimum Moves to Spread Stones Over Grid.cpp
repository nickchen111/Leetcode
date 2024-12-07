/*
2850. Minimum Moves to Spread Stones Over Grid
*/

// TC: O(mn⋅(mn)!) SC:O(mn)
class Solution {
public:
    int minimumMoves(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<pair<int,int>> from,to;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(grid[i][j] == 0) {
                    to.push_back({i,j});
                }
                else if(grid[i][j] > 1) {
                    for(int k = 0; k < grid[i][j]-1; k++) {
                        from.push_back({i,j});
                    }
                }
            }
        } 
        sort(from.begin(), from.end());
        vector<vector<pair<int,int>>> allFrom;
        auto per = [&]() -> vector<vector<pair<int,int>>> {
            vector<vector<pair<int,int>>> ret;
            vector<pair<int,int>> path;

            auto backtrack = [&](auto &&backtrack, int status) -> void {
                if(path.size() == from.size()) {
                    ret.push_back(path);
                    return;
                }
                for(int i = 0; i < from.size(); i++) {
                    if(i && from[i-1] == from[i] && ((status >> (i-1)) & 1) == 0) continue;
                    if(((status >> i) & 1) == 0) {
                        path.push_back(from[i]);
                        backtrack(backtrack, status | (1 << i));
                        path.pop_back();
                    }
                }
            };
            backtrack(backtrack,0);
            return ret;
        };
        allFrom = per();
        int idx = 0;
        int m = allFrom.size();

        int res = INT_MAX;
        do {
            int total = 0;
            for(int i = 0; i < allFrom[idx].size(); i++) { // allFrom[idx].size()
                total += abs(allFrom[idx][i].first - to[i].first) + abs(allFrom[idx][i].second - to[i].second);
                // total += abs(from[i].first - to[i].first) + abs(from[i].second - to[i].second);
            }
            res = min(res, total);
            idx += 1;
        } while(idx < m); // idx < m, next_permutation(from.begin(), from.end())

        return res;
    }
};
