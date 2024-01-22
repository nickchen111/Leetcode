/*
1377. Frog Position After T Seconds
*/

// TC:O(n) SC:O(n)
class Solution {
    double res = 0;
    using PID = pair<int, double>;
    vector<bool> visited;
public:
    double frogPosition(int n, vector<vector<int>>& edges, int t, int target) {
        if(n == 1) return 1.0;
        vector<vector<int>> graph(n+1);
        visited.resize(n+1);
        //不會跳回去
        for(auto & edge : edges){
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }
        
        BFS(graph, t, target);


        return res;
    }
    void BFS(vector<vector<int>>& graph, int t, int target){
        
        int step = -1;
        queue<PID> q;
        q.push({1,1.0}); // node -> prob

        while(!q.empty()){
            int sz = q.size();
            step += 1;
            bool flag = 0;
            while(sz--){
                int node = q.front().first;
                double curProb = q.front().second;
                q.pop();
                if(visited[node]) continue;
                visited[node] = 1;
                if(step > t){
                    flag = 1;
                    break;
                }
                //分兩種狀況 可能還沒走到底但剛好步數對上 走到底了可以無限在原地踏步直到step == t
                // corner case : target = 1 他剛好也只有一個連接點 graph[node].size() 也會只有1 但機率應該要是0
                if((target == node && step == t) || (target == node && graph[node].size() == 1 && node != 1)){
                    res = curProb;
                    flag = 1;
                    break;
                }
                
                for(auto x : graph[node]){
                    if(visited[x]) continue;
                    if(node == 1) {
                        q.push({x,curProb * (double)(1.0 / graph[node].size())});
                    }
                    else q.push({x,curProb * (double)(1.0 / (graph[node].size()-1))});
                }
            }
            if(flag) break;
        }    
    }
};

/*
此題給你一棵樹的各種節點連接表 問說一隻青蛙從root走到某點的機率  每過一秒青蛙如果還有地方可走就會以他的1/child number 機率跳到下一點 否則就會原地踏步
*/
