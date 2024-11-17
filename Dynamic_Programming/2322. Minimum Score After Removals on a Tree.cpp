/*
2322. Minimum Score After Removals on a Tree
*/

// TC:O(n^2) SC:O(n)
const int MAXN = 1005;
class Solution {
    int dfn[MAXN];
    int subtree[MAXN]; 
    int XOR_value[MAXN];
    int dfsCnt;
    vector<vector<int>> next;
    vector<int> nums;
public:
    int minimumScore(vector<int>& nums, vector<vector<int>>& edges) {
        this -> nums = nums;
        dfsCnt = 0;
        int n = nums.size();
        next.resize(n);
        for(auto &edge : edges) {
            next[edge[0]].push_back(edge[1]);
            next[edge[1]].push_back(edge[0]);
        }

        dfs(0, -1);
        int res = INT_MAX;
        for(int i = 0; i < edges.size(); i++) {
            for(int j = i + 1; j < edges.size(); j++) {
                int e1 = max(dfn[edges[i][0]], dfn[edges[i][1]]);
                int e2 = max(dfn[edges[j][0]], dfn[edges[j][1]]);
                int p1 = XOR_value[1];
                int p2 = XOR_value[e1];
                int p3 = XOR_value[e2];
                // 需判斷p2, p3 是否同一part
                if(e1 < e2 && e1 + subtree[e1] - 1 >= e2) {
                    p2 ^= p3;
                }
                else if(e2 < e1 && e2 + subtree[e2] - 1 >= e1) {
                    p3 ^= p2;
                }
                p1 ^= p2;
                p1 ^= p3;
                int maxVal = max({p1,p2,p3});
                int minVal = min({p1,p2,p3});
                res = min(res, maxVal - minVal);
            }
        }

        return res;
    }
    void dfs(int cur, int prev) {
        dfn[cur] = ++dfsCnt;
        int num = dfn[cur];
        subtree[num] = 1;
        XOR_value[num] = nums[cur];
        for(auto &nxt : next[cur]) {
            if(nxt == prev) continue;
            dfs(nxt, cur);
            subtree[num] += subtree[dfn[nxt]];
            XOR_value[num] ^= XOR_value[dfn[nxt]];
        }
    } 
};
