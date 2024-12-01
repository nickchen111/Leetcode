/*
2646. Minimize the Total Price of the Trips
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int minimumTotalPrice(int n, vector<vector<int>>& edges, vector<int>& price, vector<vector<int>>& trips) {
        int res = INT_MAX;
        vector<vector<int>> next(n);
        for(auto &e :edges) {
            next[e[0]].push_back(e[1]);
            next[e[1]].push_back(e[0]);
        }
        vector<int> freq(n);
        auto dfs0 = [&](auto &&dfs0, int cur, int prev, int target) -> bool {
            if(cur == target) {
                freq[cur] += 1;
                return true;
            }
            for(auto &nxt : next[cur]) {
                if(nxt != prev && dfs0(dfs0, nxt, cur, target)) {
                    freq[cur] += 1;
                    return true;
                } 
            }

            return false;
        };
        int m = trips.size();
        for(int i = 0; i < m; i++) {
            dfs0(dfs0, trips[i][0], -1, trips[i][1]);
        }
        vector<int> dp1(n); // 不砍半
        vector<int> dp2(n); // 砍半
        auto dfs = [&](auto &&dfs, int cur, int prev) -> void {
            dp1[cur] = freq[cur] * price[cur];
            dp2[cur] = freq[cur] * price[cur]/2;
            for(auto &nxt : next[cur]) {
                if(nxt != prev) {
                    dfs(dfs, nxt, cur);
                    dp1[cur] += min(dp1[nxt], dp2[nxt]);
                    dp2[cur] += dp1[nxt];
                }
            }
        };

        dfs(dfs, 0, -1);
        return min(dp1[0], dp2[0]);
    }
};

/*
這題給你一個機會 讓不相鄰的點可以被砍價 問說問你從某個點走到某個點可以走任意路徑，走的路徑價格加總 然後所有trips加總要最低
首先我思考的是走的路徑 如果要是最低價格的話是否走的點要最少 那就會是LCA 每個點都去計算出LCA
要計算價格的話 好像是可以先把價格加總起來 計算兩種可能的價格 一種是偶數一種是odd 看哪個少 -> 錯 他不是只能按照順序這次不要減半下次就一定要 而是可以選擇是否要減半
就變成337 house robberIII
    -
   -  -
- - -  - - - 

*/
