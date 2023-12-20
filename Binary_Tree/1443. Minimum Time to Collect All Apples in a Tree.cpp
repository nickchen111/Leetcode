/*
1443. Minimum Time to Collect All Apples in a Tree
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int minTime(int n, vector<vector<int>>& edges, vector<bool>& hasApple) {
        vector<vector<int>> graph(n);
        for(auto & edge : edges){
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }

        return DFS(-1,0,graph, hasApple);
    }

    int DFS(int prev, int cur, vector<vector<int>>& graph, vector<bool>& hasApple){
        int res = 0;
        for(auto child : graph[cur]){
            if(child != prev){
                //他下面節點是否需要走 如果要走所需花費為多少 包含下下面有頻果狀況
                int cost = DFS(cur, child, graph, hasApple);
                if(cost > 0 || hasApple[child]){
                    res += (cost + 2);
                }
            }
        }

        return res;
    }
};

/*
從原點出發 去收集子樹上有頻果的 之後收集完需返回原點 最少須走幾步
此題用BFS想的話挺複雜的 倒不如用DFS去思考 每個節點當下該返回多少給root 
如果我的節點上有頻果 ＋2 如果我的child上有 就在 + cost
*/
