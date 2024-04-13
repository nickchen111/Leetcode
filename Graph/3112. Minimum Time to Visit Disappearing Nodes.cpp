/*
3112. Minimum Time to Visit Disappearing Nodes
*/

// TC:O(nlgn) SC:O(n)
class Solution {
    using PII = pair<int,int>;
public:
    vector<int> minimumTime(int n, vector<vector<int>>& edges, vector<int>& disappear) {
        vector<vector<PII>> graph(n);
        vector<int> dist(n,INT_MAX/2);
        dist[0] = 0;
        for(auto edge : edges){
            graph[edge[0]].push_back({edge[1], edge[2]});
            graph[edge[1]].push_back({edge[0], edge[2]});
        }
        priority_queue<PII, vector<PII>, greater<PII>> pq;
        pq.push({0,0});
        vector<int> visited(n);
        while(!pq.empty()){
            int sz = pq.size();
            while(sz--){
                int curNode = pq.top().second;
                int time = pq.top().first;
                pq.pop();
                if(time >= disappear[curNode]) continue;
                if(visited[curNode]) continue;
                visited[curNode] = 1;
                for(auto [nxt, nxtTime] : graph[curNode]){
                    int nextTime = time + nxtTime;
                    if(nextTime < dist[nxt]){
                        if(nextTime < disappear[nxt]){
                            dist[nxt] = nextTime;
                            pq.push({nextTime, nxt});  
                        }
                    }
                }
            }
        }
        vector<int> res(n,-1);
        for(int i = 0; i < n; i++){
            if(dist[i] != INT_MAX/2) res[i] = dist[i];
        }
        
        return res;
    }
};

/*
給你 edge 以及他們需要走到彼此的時間
然後還有一個數組描述某一點消失的時間 該點如果消失就不能訪問了
問說 從node 0出發到每點訪問的最短時間為多少
從某一點到某一點最短距離 dijstra
這題單純多了一個條件判斷一下 disappaer 看你要加入的點是否時間已經超過該點消失的期限 是的話就不用加入了 因為走不到他
*/
