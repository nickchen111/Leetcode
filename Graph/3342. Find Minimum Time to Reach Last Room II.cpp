/*
3342. Find Minimum Time to Reach Last Room II
*/

// TC:O(2*n*m* lg(2*n*m)) SC:O(2*n*m)
class Solution {
public:
    int minTimeToReach(vector<vector<int>>& moveTime) {
        int n = moveTime.size();
        int m = moveTime[0].size();
        priority_queue<vector<int>, vector<vector<int>>, greater<>> pq; // 使用時間, 座標x,y, 上次跳的時間
        
        pq.push({0,0,0,0});
        
        vector<vector<vector<int>>> dist(n, vector<vector<int>>(m, vector<int>(3, INT_MAX/2)));
        dist[0][0][0] = 0;
        vector<int> dirs = {0,1,0,-1,0};
        while(!pq.empty()) {
            vector<int> tmp = pq.top();
            pq.pop();
            int curTime = tmp[0];
            int x = tmp[1];
            int y = tmp[2];
            if(x == n-1 && y == m-1) return curTime;
            int curLast = tmp[3];
            if(dist[x][y][curLast] < curTime) continue;
            dist[x][y][curLast] = curTime;
            for(int i = 1; i < dirs.size(); i++) {
                int nx = dirs[i-1] + x;
                int ny = dirs[i] + y;
                int nextLast = (curLast == 0 || curLast == 2) ? 1 : 2;
                if(nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
                int nextTime = max(moveTime[nx][ny], curTime) + nextLast;
                if(dist[nx][ny][nextLast] > nextTime) {
                    dist[nx][ny][nextLast] = nextTime;
                    pq.push({nextTime, nx, ny, nextLast});
                }
            }
        }
        
        return -1;
    }
};
