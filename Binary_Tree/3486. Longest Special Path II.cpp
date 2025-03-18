// TC:O(n) SC:O(n)
class Solution {
public:
    vector<int> longestSpecialPath(vector<vector<int>>& edges, vector<int>& nums) {
        int n = nums.size();
        vector<vector<pair<int,int>>> next(n);
        for(auto &e : edges) {
            next[e[0]].emplace_back(e[1], e[2]);
            next[e[1]].emplace_back(e[0], e[2]);
        }
        unordered_map<int, int> last_pos;
        int maxLen = 0;
        int minNode = INT_MAX;
        vector<int> presum = {0};
        auto dfs = [&](auto &&dfs, int cur, int prev, int last1, int top_depth) -> void {
            int color = nums[cur];
            int last2 = last_pos[color]; // 目前可能出現重複的點的上個位置
            top_depth = max(top_depth, min(last1, last2));
            if (presum.back() - presum[top_depth] > maxLen) {
                maxLen = (presum.back() - presum[top_depth]);
                minNode = (int) presum.size() - top_depth;
            } else if(presum.back() - presum[top_depth] == maxLen) minNode = min(minNode, (int) presum.size() - top_depth);
            last_pos[color] = presum.size();
            for (auto &[nxt, w] : next[cur]) {
                if(nxt != prev) {
                    presum.emplace_back(presum.back() + w);
                    dfs(dfs, nxt, cur, max(last1, last2), top_depth);
                    presum.pop_back();
                }
            }
            last_pos[color] = last2;
        };
        dfs(dfs, 0, -1, 0, 0);
        return {maxLen, minNode};
    }
};
