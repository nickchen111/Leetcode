/*
1514. Path with Maximum Probability
*/


class Solution {
public:
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start_node, int end_node) {
        
        int v = edges.size();
        //構造graph 鄰接表
        vector<vector<pair<int, double>>> graph(n);
        for(int i = 0; i < v; i++){
            graph[edges[i][0]].push_back({edges[i][1], succProb[i]});
            graph[edges[i][1]].push_back({edges[i][0], succProb[i]});
        }
        //開始dijkstra 思考它的定義 bfs+貪心+priority queue 
        
        return dijkstra(graph, start_node, end_node);

    }

    double dijkstra(vector<vector<pair<int, double>>>& graph, int start, int end){
        //想創建一個表去得知從start到每一點的最大成功率
        vector<double> proto(graph.size(), -1); //先給一個最低的不可能到的值
        proto[start] = 1;

        //開始用priority queue的方式從start遍歷
        priority_queue<pair<double, int>, vector<pair<double, int>>, less<pair<double, int>>> pq;
        pq.push({1.0, start});

        while(!pq.empty()){
            auto cur = pq.top();
            pq.pop();
            double prob = cur.first;
            int curNode = cur.second;
            if(proto[curNode] > prob) continue;

            if(curNode == end) return prob;

            for(auto neighbor:graph[curNode]){
                int nextNode = neighbor.first;
                double toNextProb = proto[curNode]*neighbor.second;
                if(proto[nextNode] < toNextProb ){
                    proto[nextNode] = toNextProb;
                    pq.push({toNextProb, nextNode});
                }
            }
        }
        return 0; //代表到不了
    }
};

/*
解題思路：
求最大的機率 無向圖-->其實還是可以用dijkstra  無向圖就是雙向圖 求最大的機率 跟最小最短似乎相反
但是為何dijkstra是求最小 因為多加一個edge就會超過 那是不是跟此題一樣 多乘一個edge就會更小
tc: o(ElgE) sc: o(n+E)
*/

//la大
// struct 不再需要声明，直接在结构体内进行定义
class Solution {
public:
    double maxProbability(int n, vector<vector<int>>& edges, vector<double>& succProb, int start, int end) {
        vector<vector<pair<double, int>>> graph(n);
        for (int i = 0; i < edges.size(); i++) {
            int from = edges[i][0];
            int to = edges[i][1];
            double weight = succProb[i];
            // 无向图其实就是双向图
            graph[from].push_back(make_pair(weight, to));
            graph[to].push_back(make_pair(weight, from));
        }
        return dijkstra(start, end, graph);
    }

    struct State {
        int id;
        double distFromStart;
        State(int id, double distFromStart) : id(id), distFromStart(distFromStart) {}
        bool operator < (const State& rhs) const {
            return distFromStart < rhs.distFromStart;
        }
    };

    double dijkstra(int start, int end, vector<vector<pair<double, int>>>& graph) {
        int V = graph.size();
        vector<double> distTo(V, -1);
        distTo[start] = 1;
        priority_queue<State> pq;
        pq.push(State(start, 1));
        while (!pq.empty()) {
            State curState = pq.top();
            pq.pop();
            int curNodeID = curState.id;
            double curDistFromStart = curState.distFromStart;
            if (curNodeID == end) {
                return curDistFromStart;
            }
            if (curDistFromStart < distTo[curNodeID]) {
                continue;
            }
            for (auto neighbor : graph[curNodeID]) {
                int nextNodeID = neighbor.second;
                double distToNextNode = distTo[curNodeID] * neighbor.first;
                if (distTo[nextNodeID] < distToNextNode) {
                    distTo[nextNodeID] = distToNextNode;
                    pq.push(State(nextNodeID, distToNextNode));
                }
            }
        }
        return 0.0;
    }
};
