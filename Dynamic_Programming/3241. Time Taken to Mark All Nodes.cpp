/*
3241. Time Taken to Mark All Nodes
*/

// TC:O(n) SC:O(n)
class Solution {
    vector<tuple<int,int,int>> nodes;
    vector<vector<int>> next;
    vector<int> res;
public:
    vector<int> timeTaken(vector<vector<int>>& edges) {
        int n = edges.size();
        nodes.resize(n+1);
        next.resize(n+1);
        res.resize(n+1);
        for(auto edge : edges){
            next[edge[0]].push_back(edge[1]);
            next[edge[1]].push_back(edge[0]);
        }

        DFS(0,-1);
        reRoot(0, -1, 0);

        return res;

    }
    int DFS(int x, int pa){
        int max_d = 0, max_d2 = 0, my = 0;
        for(auto y : next[x]){
            if(y == pa) continue;
            int depth = DFS(y,x) + (y+1)%2+1;
            if(depth > max_d){
                max_d2 = max_d;
                max_d = depth;
                my = y;
            }
            else if(depth > max_d2){
                max_d2 = depth;
            }
        }

        nodes[x] = {max_d, max_d2, my};

        return max_d;
    }
    void reRoot(int x, int pa, int from_up){
        auto &[max_d, max_d2, my] = nodes[x];
        res[x] = max(max_d, from_up);

        for(auto y : next[x]){
            if(y == pa) continue;
            reRoot(y, x, max(from_up, (y == my ? max_d2:max_d)) + (x+1)%2+1);
        }
    }
};

/*
維護最大根次大深度 最大根深是從哪個子節點來
*/s
