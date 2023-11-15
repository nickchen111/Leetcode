/*
2925. Maximum Score After Applying Operations on a Tree
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
