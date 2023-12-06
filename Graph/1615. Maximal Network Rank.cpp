/*
1615. Maximal Network Rank
*/

// TC:O(n^2) SC:O(n)
class Solution {
public:
    int maximalNetworkRank(int n, vector<vector<int>>& roads) {
        vector<int> edge(n);
        //紀錄每個點有多少條邊
        vector<vector<int>> graph(n, vector<int>(n,0));
        for(auto road:roads){
            edge[road[0]]+=1;
            edge[road[1]]+=1;
            graph[road[0]][road[1]] = 1;
            graph[road[1]][road[0]] = 1;
        }

        int res = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(i != j){
                    int sum = edge[i] + edge[j];
                    if(graph[i][j] == 1) sum-=1;
                    res = max(res, sum);
                }
            }
        }

        return res;
        
    }
};
