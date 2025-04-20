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
        power = log2(n); // 或者可以直接bit_width(unsigned(n));
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
    // 如何LCA計算兩點的LCA for 在線查詢
    int LCA(int a, int b){
        if(deep[a] < deep[b]) {
            int tmp = a;
            a = b;
            b = tmp;
        }
        for(int p = power; p >= 0; p--) {
            if(deep[stjump[a][p]] >= deep[b]) {
                a = stjump[a][p];
            }
        }
    
        if(a == b) return a;
        for(int p = power; p >= 0; p--) {
            if(stjump[a][p] != stjump[b][p]) {
                a = stjump[a][p];
                b = tjump[b][p];
            }
        }
    
        return stjump[a][0];
      
    }
};
