/*
815. Bus Routes
*/


// 2/21
class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
        unordered_map<int, vector<int>> graph; // 這些站可以從哪輛公車抵達
        
        for(int i = 0; i < routes.size(); i++){
            for(int j = 0; j < routes[i].size(); j++){
                graph[routes[i][j]].push_back(i);
            }
        }

        queue<int> q;
        vector<bool> visitedStop(1000005);
        vector<bool> visitedBus(505);
        visitedStop[source] = 1;
        q.push(source); 
        int step = -1;
        while(!q.empty()){
            int sz = q.size();
            step += 1;
            while(sz--){
                int curStop = q.front();
                q.pop();
                if(curStop == target) return step;
                //這一站可以搭哪些公車
                for(auto bus : graph[curStop]){
                    if(visitedBus[bus]) continue;
                    visitedBus[bus] = 1;
                    for(auto nextStop : routes[bus]){
                        if(visitedStop[nextStop]) continue;
                        visitedStop[nextStop] = 1;
                        q.push(nextStop);
                    }
                }
            }
        }

        return -1;
    }
};


// TC:O(m*n) m為公車數量 n為公車停靠站數目 SC:O(m+n)
class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
        if(source == target) return 0;
        unordered_map<int,vector<int>> stop2bus;
        for(int i = 0; i<routes.size(); i++){
            for(auto j:routes[i]){
                stop2bus[j].push_back(i);
            }
        }
        queue<int> q;
        q.push(source);
        unordered_set<int> visitedStop;
        unordered_set<int> visitedBus;
        visitedStop.insert(source);
        int res = -1;
        while(!q.empty()){
            int sz = q.size();
            res+=1;
            for(int i = 0; i<sz; i++){
                int cur = q.front();
                q.pop();
                //每個站點能選擇的bus
                for(auto bus:stop2bus[cur]){
                    //每個公車可以到的下一個stop
                    if(visitedBus.find(bus) != visitedBus.end()) continue;
                    visitedBus.insert(bus);
                    for(auto nextStop: routes[bus]){
                        if(visitedStop.find(nextStop) != visitedStop.end()) continue;
                        if(nextStop == target) return res+1;
                        
                        visitedStop.insert(nextStop);
                        q.push(nextStop);
                    }
                }
            }
        }

        return -1;
    }
};
