/*
2925. Maximum Score After Applying Operations on a Tree
*/

// 1204 TC:O(V+E) SC:O(V)
class Solution {
    using LL = long long;
public:
    long long maximumScoreAfterOperations(vector<vector<int>>& edges, vector<int>& values) {
        int n = values.size();
        vector<vector<int>> next(n);
        vector<LL> subtree(n);
        for(auto &e : edges) {
            next[e[0]].push_back(e[1]);
            next[e[1]].push_back(e[0]);
        }
        auto dfs0 = [&](auto &&dfs0, int cur, int prev) -> LL {
            LL sum = values[cur];
            for(auto &nxt : next[cur]) {
                if(nxt == prev) continue;
                sum += dfs0(dfs0, nxt, cur);
            }
            subtree[cur] = sum;
            return sum;
        };
        dfs0(dfs0, 0, -1);

        auto dfs = [&](auto &&dfs, int cur, int prev) -> LL {
            if(next[cur].size() == 1 && cur != 0) return 0; // 這個不選
            LL choose = values[cur];
            LL not_choose = 0;
            for(auto &nxt : next[cur]) {
                if(nxt == prev) continue;
                choose += dfs(dfs, nxt, cur); // 後面都有個不選的
            }
            not_choose = max((LL)subtree[cur] - values[cur], choose);
            return not_choose;
        };
        return dfs(dfs, 0, -1);
    }
};

/*
選or不選
選了 我前面就必須有人不選
不選 我前面都可以選

每個點討論是否選
選他拿他的值 = 後面的要有不選的最大值 + 拿到的值
不選不拿他的值 = 後面都選拿到的值
max(我不選 + 後面都選, 我選 + 後面有個不選)
*/

//
class Solution {
    vector<vector<int>> next;
    long long subtreesum[20005];
public:
    long long maximumScoreAfterOperations(vector<vector<int>>& edges, vector<int>& values) {
        int n = values.size();
        next.resize(n);
        for(auto edge:edges){
            next[edge[0]].push_back(edge[1]);
            next[edge[1]].push_back(edge[0]);
        }

        
        DFS0(0,-1,values);
        

        return DFS(0,-1,values);
    }

    long long DFS(int node, int parent, vector<int>& values){
        //node != 0 conrner case 只有一條邊兩個點 or確實是一條的path沒有其他分支
        if(next[node].size() == 1 && node != 0) return 0;

        long long sum = values[node];
        //開始計算此節點取了之後後面最大的sum是多少
        for(auto x:next[node]){
            if(x == parent) continue;//不走回頭路
            sum+=DFS(x,node,values);
        }

        return max(sum,subtreesum[node] - values[node]);
    }
    long long DFS0(int cur, int parent, vector<int>& values){
        long long sum = values[cur];
        for(auto x:next[cur]){
            if(x == parent) continue;
            sum+=DFS0(x,cur,values);
        }
        subtreesum[cur] = sum;
        return sum;
    }
};


// TC:O(V+E) SC:O(V)
class Solution {
    vector<vector<int>> next;
public:
    long long maximumScoreAfterOperations(vector<vector<int>>& edges, vector<int>& values) {
        int n = values.size();
        next.resize(n);
        for(auto edge:edges){
            next[edge[0]].push_back(edge[1]);
            next[edge[1]].push_back(edge[0]);
        }

        long long res = 0;
        for(auto v:values){
            res+=v;
        }
        long long x = DFS(0,-1,values);

        return res-x;
    }

    long long DFS(int node, int parent, vector<int>& values){
        //node != 0 conrner case 只有一條邊兩個點 or確實是一條的path沒有其他分支
        if(next[node].size() == 1 && node != 0) return values[node];

        long long sum = 0;
        //開始計算此節點下的sum是多少
        for(auto x:next[node]){
            if(x == parent) continue;//不走回頭路
            sum+=DFS(x,node,values);
        }

        return min(sum,(long long)values[node]);
    }
};

/*
從root 到leaf 有個不是0即可
*/
