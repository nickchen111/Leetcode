/*
1928. Minimum Cost to Reach Destination in Time
*/
 
// 尚未剪枝  TC: O(n * maxTime * E) SC: O(n * maxTime * E)
class Solution {
public:
    int minCost(int maxTime, vector<vector<int>>& edges, vector<int>& passingFees) {
        //edge 城市到城市之間的時間 passingFees 每個城市花費
        int n = passingFees.size();
        auto visited = vector<vector<int>>(n, vector<int>(100001,INT_MAX/2)); // visited[城市][時間] = 花費
        visited[0][0] = passingFees[0];

        vector<vector<pair<int,int>>> graph(1001);
        for(const auto &edge:edges){
            graph[edge[0]].push_back({edge[1],edge[2]});
            graph[edge[1]].push_back({edge[0],edge[2]});
        }
        //從city 0 到 city n-1最佳走法
        queue<pair<int,int>> q; //城市 時間 
        q.push({0,0});

        while(!q.empty()){
            int city = q.front().first;
            int time = q.front().second;
            int Fee = visited[city][time];
            q.pop();

            for(const auto& [nextCity, nextTime]:graph[city]){
                int newTime = time+nextTime;
                int newFee = Fee + passingFees[nextCity];
                if(visited[nextCity][newTime] <= newFee) continue;
                if(newTime > maxTime) continue;

                visited[nextCity][newTime] = newFee;
                q.push({nextCity, newTime});
            }
        }

        int res = INT_MAX/2;
        for(int i = 0; i <= maxTime; i++){
            res = min(res, visited[n-1][i]);
        }
        if(res == INT_MAX/2) return -1;
        else return res;

    }
};


// 剪枝 TC: O(n * maxTime * E) SC: O(n * maxTime * E)
class Solution {
public:
    int minCost(int maxTime, vector<vector<int>>& edges, vector<int>& passingFees) {
        //edge 城市到城市之間的時間 passingFees 每個城市花費
        int n = passingFees.size();
        auto visited = vector<vector<int>>(n, vector<int>(100001,INT_MAX/2)); // visited[城市][時間] = 花費
        visited[0][0] = passingFees[0];
        //小小剪枝技巧
        vector<int> earlistTime(n+1, INT_MAX);
        

        vector<vector<pair<int,int>>> graph(1001);
        for(const auto &edge:edges){
            graph[edge[0]].push_back({edge[1],edge[2]});
            graph[edge[1]].push_back({edge[0],edge[2]});
        }
        //從city 0 到 city n-1最佳走法
        queue<pair<int,int>> q; //城市 時間 
        q.push({0,0});

        while(!q.empty()){
            int city = q.front().first;
            int time = q.front().second;
            int Fee = visited[city][time];
            q.pop();

            for(const auto& [nextCity, nextTime]:graph[city]){
                int newTime = time+nextTime;
                int newFee = Fee + passingFees[nextCity];
                if(visited[nextCity][newTime] <= newFee) continue;
                //剪枝
                if(newTime > earlistTime[nextCity] && newFee > visited[nextCity][newTime]) continue;
                if(newTime > maxTime) continue;
                if(newFee < visited[nextCity][newTime]){
                     earlistTime[nextCity] = min(earlistTime[nextCity], newTime);
                    visited[nextCity][newTime] = newFee;
                    q.push({nextCity, newTime});
                }
            }
        }

        int res = INT_MAX/2;
        for(int i = 0; i <= maxTime; i++){
            res = min(res, visited[n-1][i]);
        }
        if(res == INT_MAX/2) return -1;
        else return res;

    }
};

/*
此題問說從A城市到B城市會花時間 並且到了一個城市都會花錢 問說時間不超過某上限狀況 能夠花費的最少錢為多少？
*/
