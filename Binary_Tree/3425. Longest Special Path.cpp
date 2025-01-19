// TC:O(n) SC:O(n)
class Solution {
public:
    vector<int> longestSpecialPath(vector<vector<int>>& edges, vector<int>& nums) {
        int n = nums.size();
        vector<vector<pair<int, int>>> next(n);
        int maxLen = 0;
        int minNodes = INT_MAX;
        // pair<int,int> ans = {-1,0};
        for (auto& e : edges) {
            next[e[0]].push_back({e[1], e[2]});
            next[e[1]].push_back({e[0], e[2]});
        }
        
        vector<int> presum = {0};
        unordered_map<int,int> last_pos; // 某個顏色他上次出現的位置的下個位置 注意要+1去指向他的下一個位置
        auto dfs = [&](auto&& dfs, int cur, int prev, int top_depth) -> void {
            int color = nums[cur];
            int old_depth = last_pos[color];
            top_depth = max(top_depth, old_depth); // 代表 現在走到的這個節點 往上走 是會先卡到當前顏色重複的node 還是既有高度就已經很低了
            // ans = max(ans, {presum.back() - presum[top_depth], top_depth - (int)presum.size()}); // 這樣就不用寫if else 將第二項轉成負數
            if(presum.back() - presum[top_depth] > maxLen) {
                maxLen = presum.back() - presum[top_depth];
                minNodes = presum.size() - top_depth;
            }
            else if(presum.back() - presum[top_depth] == maxLen) {
                minNodes = min(minNodes, (int)presum.size() - top_depth);
            }
            last_pos[color] = presum.size();
            for (auto &[nxt, w] : next[cur]) {
                if (nxt == prev) continue;
                presum.push_back(presum.back() + w);
                dfs(dfs, nxt, cur, top_depth);
                presum.pop_back();
            }
            last_pos[color] = old_depth;
        };
        dfs(dfs, 0, -1, 0);

        return {maxLen, minNodes == INT_MAX ? 1 : minNodes}; // {ans.first, -ans.second};
    }
};
