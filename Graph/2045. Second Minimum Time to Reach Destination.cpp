/*
2045. Second Minimum Time to Reach Destination
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int secondMinimum(int n, vector<vector<int>>& edges, int time, int change) {
        vector<vector<int>> next(n+1);
        for(auto edge : edges){
            next[edge[0]].push_back(edge[1]);
            next[edge[1]].push_back(edge[0]);
        }

        int minVal = -1;
        queue<pair<int,int>> q;
        vector<int> visited(n+1);
        q.push({1,0});
        vector<int> dist(n+1,-1);
        dist[1] = 0;
        while(!q.empty()){
            int sz = q.size();
            while(sz--){
                int cur = q.front().first;
                int curTime = q.front().second;
                q.pop();
                visited[cur] += 1;
                if(cur == n && minVal != -1 && visited[cur] == 2) return curTime;
                if(cur == n) minVal = curTime;
                for(auto nxt : next[cur]){
                    int check = curTime/change;
                    int nextTime = curTime + time;
                    if(check % 2){
                        nextTime += change - (curTime%change);
                    }
                    // 確保走過不超過2次 並且 這次走的路徑要比上次長 較短就不會是第二短路徑惹
                    if(visited[nxt] <= 1 && dist[nxt] < nextTime){
                        dist[nxt] = nextTime;
                        q.push({nxt, nextTime});
                    }
                } 
            }
        }

        return -1;
    }
};


/*
change的偶數倍數會是綠燈 奇數會是紅燈 走到第二次可遇到n的路徑就對了
*/
