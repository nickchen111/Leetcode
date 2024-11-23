/*
1483. Kth Ancestor of a Tree Node
*/

// TC:O(n*lgn + m*power + n) SC:O(n)
class TreeAncestor {
    vector<vector<int>> next;
    vector<int> deep;
    vector<vector<int>> stjump;
    int power;
public:
    TreeAncestor(int n, vector<int>& parent) {
        // 建造圖，如果要知道自己之前的parent 回頭traverse n^2
        next.resize(n);
        deep.resize(n);
        power = log2(n);
        stjump.resize(n, vector<int>(power+1));
        for(int i = 0; i < parent.size(); i++) {
            if(parent[i] != -1) {
                next[parent[i]].push_back(i);
            }
        }
        dfs(0, 0);
        
    }
    
    int getKthAncestor(int node, int k) {
        if(deep[node] <= k) return -1;
        int s = deep[node] - k; // 想抵達的深度
        for(int p = power; p >= 0; p--) {
            if(deep[stjump[node][p]] >= s) {
                node = stjump[node][p];
            }
        }

        return node;
    }
    int log2(int n) {
        int ans = 0;
        while((1<<ans) <= (n >> 1)) {
            ans ++;
        }

        return ans;
    }
    void dfs(int cur, int prev) {
        if(cur == 0) deep[cur] = 1;
        else deep[cur] = deep[prev] + 1;
        stjump[cur][0] = prev;
        for(int p = 1; (1 << p) <= deep[cur]; p++) {
            stjump[cur][p] = stjump[stjump[cur][p-1]][p-1];
        }
        for(auto &nxt : next[cur]) {
            dfs(nxt, cur);
        }
    }
};

/**
 * Your TreeAncestor object will be instantiated and called as such:
 * TreeAncestor* obj = new TreeAncestor(n, parent);
 * int param_1 = obj->getKthAncestor(node,k);
 */

 /*
 如果要知道自己之前的parent 回頭traverse n^2
 要有更高效的方式 也就是樹上倍增 lgn定位到
 */
