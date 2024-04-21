/*
3123. Find Edges in Shortest Paths
*/

// TC:O(nlgn) SC:O(n*3)
class Solution {
    using PII = pair<int,int>;
public:
    vector<bool> findAnswer(int n, vector<vector<int>>& edges) {
        int m = edges.size();
        vector<vector<array<int,3>>> graph(n); 
        vector<bool> res(edges.size(),false);
        for(int i = 0; i < m; i++){
            graph[edges[i][0]].push_back({edges[i][1],edges[i][2],i});
            graph[edges[i][1]].push_back({edges[i][0],edges[i][2],i});
        }
        
        priority_queue<PII, vector<PII>, greater<PII>> pq; // dist, node
        pq.push({0,0});
        
        vector<int> minDist1(n,INT_MAX/2);
        
        while(!pq.empty()){
            int sz = pq.size();
            while(sz--){
                int cur = pq.top().second;
                int dist = pq.top().first;
                
                pq.pop();
                if(minDist1[cur] != INT_MAX/2) continue;
                minDist1[cur] = dist;
                
                for(auto [nxtNode, nxtDist, idx] :  graph[cur]){
                    if(nxtDist + dist < minDist1[nxtNode]){
                        pq.push({nxtDist + dist, nxtNode});
                    }
                }
            }
        }
        
        
        vector<int> minDist2(n, INT_MAX/2);
        pq.push({0,n-1});
        
        while(!pq.empty()){
            int sz = pq.size();
            while(sz--){
                int cur = pq.top().second;
                int dist = pq.top().first;
                pq.pop();
                if(minDist2[cur] != INT_MAX/2) continue;
                minDist2[cur] = dist;
                for(auto [nxtNode, nxtDist, idx] : graph[cur]){
                    if(minDist1[nxtNode] + dist + nxtDist == minDist1[n-1]){
                        res[idx] = true;
                    }
                    if(nxtDist + dist < minDist2[nxtNode]){
                        pq.push({nxtDist + dist, nxtNode});
                    }
                }
            }
        }
        
       
        
        return res;
        
    }
};

/*
問說題目給你的edge是否是 node 0 - node n-1眾多最短路徑的其中一條edge
用dijkstra 且可以用相反方向的dijkstra 在坐反方向的過程中做兩點之間距離加總判斷是否為最短距離
*/
