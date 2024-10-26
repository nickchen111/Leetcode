/*
3331. Find Subtree Sizes After Changes
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();
        vector<vector<int>> next(n); 
        
        for(int i = 1; i < n; i++) {
            next[parent[i]].push_back(i);
        }
        
        vector<int> lastPos(26,-1);
        vector<int> newParent = parent;
        
        function<void(int node,vector<int>& lastPos)> dfs0 = [&](int node,vector<int>& lastPos) -> void {
            if(lastPos[s[node]-'a'] != -1) {
                newParent[node] = lastPos[s[node]-'a'];
            }
            
            int prev = lastPos[s[node]-'a'];
            lastPos[s[node]-'a'] = node;
            
            for(auto &nxt : next[node]) {
                dfs0(nxt, lastPos);
            }
            
            lastPos[s[node]-'a'] = prev;
        };
        
        dfs0(0,lastPos);
        
        vector<vector<int>> newNext(n);
        for(int i = 1; i < n; i++) {
            newNext[newParent[i]].push_back(i);
        }
        
        vector<int> size(n);
        function<int(int node)> dfs = [&](int node) -> int {
            int total = 1;
            for(int child : newNext[node]) {
                total += dfs(child);
            }
            size[node] = total;
            return total;
        };
        
        dfs(0);
        
        return size;
    }
};
