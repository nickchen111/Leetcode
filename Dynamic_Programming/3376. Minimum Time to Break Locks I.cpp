/*
3376. Minimum Time to Break Locks I
*/

// 次佳解 TC:O(n *n! + nlgn) SC:O(n!)
class Solution {
public:
    int findMinimumTime(vector<int>& strength, int K) {
        int n = strength.size();
        sort(strength.begin(), strength.end());
        vector<vector<int>> allper;
        auto per = [&]() -> vector<vector<int>> {
            vector<vector<int>> ret;
            vector<int> path;
            auto back = [&](auto &&back, int status) -> void {
                if(path.size() == n) {
                    ret.push_back(path);
                }
                for(int i = 0; i < n; i++) {
                    if(i && strength[i-1] == strength[i] && ((status >> i)&1) == 0 && ((status >> (i-1))&1) == 0) continue;
                    if(((status >> i) & 1) == 0) {
                        path.push_back(strength[i]);
                        back(back, status | (1<<i));
                        path.pop_back();
                    }
                }
            };
            back(back, 0);
            return ret;
        };
        allper = per();
        int m = allper.size();
        int res = INT_MAX;
        for(int i = 0; i < m; i++) {
            int inc = 1;
            int time = allper[i][0] - 1;
            int curE = allper[i][0];
            int idx = 0;
            while(idx < allper[i].size()) {
                time += 1;
                if(curE < allper[i][idx]) {
                    time += (allper[i][idx] - curE) / inc + ((allper[i][idx] - curE) % inc == 0 ? 0 : 1);
                }
                curE = 0;
                inc += K;
                curE += inc;
                idx += 1;
            }
            res = min(res, time);
        }
        
        return res;
        
    }
};
