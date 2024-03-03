/*
3067. Count Pairs of Connectable Servers in a Weighted Tree Network
*/

// TC:O(n^2) SC:O(n)
class Solution {
    vector<pair<int,int>> next[1005];
    int signalSpeed;
public:
    vector<int> countPairsOfConnectableServers(vector<vector<int>>& edges, int signalSpeed) {
        this ->  signalSpeed =  signalSpeed;
        int n = edges.size() + 1;
        
        for(auto e : edges){
            next[e[0]].push_back({e[1],e[2]});
            next[e[1]].push_back({e[0],e[2]});
        }
        
        vector<int> res(n);
        for(int i = 0; i < n; i++){
            if(next[i].size() == 1) continue;
            //可以當中間點的node
            vector<int> count;
            for(auto [nxt, w] : next[i]){
                unordered_map<int,int> map;
                map[w % signalSpeed] += 1;
                DFS(nxt, i, w,map);
                if(map.find(0) != map.end()){
                    count.push_back(map[0]);
                }
            }
            for(int a = 0; a < count.size(); a++){
                for(int b = a + 1; b < count.size(); b++){
                    res[i] += count[a]*count[b];
                }
            }
        }
        
        return res;
    }
    void DFS(int cur, int parent, int dist, unordered_map<int,int>& map){
        for(auto [nxt,w] : next[cur]){
            if(nxt == parent) continue;
            map[(w+dist) % signalSpeed] += 1;
            DFS(nxt, cur, (dist+w)%signalSpeed, map);
        }
    }
};

/*
此題要去求 以某個點當中間點 其他的點到彼此之間 經過中間點時的距離兩點的話會有兩段 這兩段距離是否都可以被 signalSpeed整除 
這樣的中間點與兩點的數量有多少個
除了edge 以外的node 都出發去收集看看他之後可以有多少種符合條件的長度 然後 將以他為中間點的符合條件的所有邊長做乘法
*/
