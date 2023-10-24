/*
787. Cheapest Flights Within K Stops
*/
// 10/19
class Solution {
    //dijkstra
    struct state{
        int a;
        int dist;
        int count;
        state(int a, int dist, int count){
            this->a = a;
            this->dist = dist;
            this->count = count;
        }
        bool operator>(const state& other) const{
            return dist > other.dist;
        }
    };
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        //build graph
        vector<vector<pair<int,int>>> graph(n);
        for(auto flight:flights){
            graph[flight[0]].push_back({flight[1], flight[2]});
        }
 

        vector<vector<int>> minDist(n, vector<int>(k+2, INT_MAX/2));
        priority_queue<state, vector<state>, greater<state>> pq;
        pq.push({src,0, 0});

        while(!pq.empty()){
            state cur = pq.top();
            pq.pop();
            int a = cur.a;
            int dist = cur.dist;
            int count = cur.count;

            if(a == dst) return dist;
            if(count == k+1) continue;
            if(minDist[a][count] < INT_MAX/2) continue;
            minDist[a][count] = dist;

            for(auto ticket:graph[a]){
                auto [next, price] = ticket;
                if(minDist[next][count+1] < INT_MAX/2) continue;
                pq.push({next,price+dist,count+1});
            }
        }

        return -1;
    }
};
//dijkstra TC:O(n*lgn) SC:O(n*k)
class Solution {
public:
    struct state{
        int id;
        int costFromsrc;
        int count;
        state(int id, int costFromsrc, int count){
            this->id = id;
            this->costFromsrc =costFromsrc;
            this->count = count;
        }
        bool operator> (const state& other) const{
            return costFromsrc > other.costFromsrc;
        }
    };
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        
        vector<vector<pair<int,int>>> graph(n);
        for(auto flight:flights){
            int from = flight[0];
            int dest = flight[1];
            int price = flight[2];
            graph[from].push_back({dest, price});
        }
       
        vector<vector<int>> cost(n,vector<int>(k+2, INT_MAX/2));//大家跟src距離
        cost[src][0] = 0;

        priority_queue<state, vector<state>, greater<state>> pq;
        pq.push(state(src, 0, 0));

        while(!pq.empty()){
            state cur = pq.top(); pq.pop();
            int curid = cur.id;
            int curcost = cur.costFromsrc;
            int time = cur.count;

            if(curid == dst) return curcost;
            if(time == k+1) continue;
            if(curcost > cost[curid][time]) continue;// or if(curcost < INT_MAX/2) continue
            //按照HG大對dijkstra的說明 第一個被彈出來的就是到那個點最短的路徑 所以後面做到一樣的都可以pass


            for(auto neighbor: graph[curid]){
                int nextprice = curcost+neighbor.second;
                int nextId = neighbor.first;
                int nextcount = time +1;

                if(nextprice < cost[nextId][nextcount]){
                    cost[nextId][nextcount] = nextprice;
                    pq.push(state(nextId, nextprice, nextcount));
               }
            }
        }
        return -1;
    }
};




/*
此題是最小路徑和加上停止次數的限制 
可以用dijkstra or DP來做

*/
