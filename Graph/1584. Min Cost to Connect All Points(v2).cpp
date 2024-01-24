/*
用struct state方式去做priority queue
切記要讓要排序的項目首先被加進queuq裡面
*/

//TC:O(ELGE) if E = N^2 就會是 n^2(lgn)偏大 SC:O(n^2) from priority queue n^2個邊
class Solution {   
    // kruskal 1. 選取最短路徑 但因為每條路都要連再一起 所以要用uniond find去連起來
    class UF{
        int parent[1000];
        int count;
    public:
        UF(int n){
            this->count = n;
            for(int i = 0; i < n; i++){
                parent[i] = i;
            }
        }
        int find(int x){
            if(x != parent[x]){
                parent[x] = find(parent[x]);
            }

            return parent[x];
        }

        void union_(int x, int y){
           int rootx = find(x);
           int rooty = find(y);
           if(rootx != rooty){
               parent[rootx] = rooty;
               count--;
           } 
           else return;
        }  
    };
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        if(n==1) return 0;
        priority_queue<state, vector<state>, greater<state>> edges;
        //建立點跟點之間關係圖
        for(int i = 0; i<n; i++){
            for(int j = i+1; j <n; j++){
                    int xi = points[i][0]; int yi = points[i][1];
                    int xj = points[j][0]; int yj = points[j][1];
                    int dist = abs(xi - xj) + abs(yi - yj);
                    edges.push(state(dist, i, j));//必須把要排序的放前面
            }
        }



        //開始從最小的開始拿出來使用
        int edgenum= 0; //邊數到n-1條就肯定是最小的
        int ans = 0; //紀錄最短路徑
        UF uf(n);// 先建立大家各自都是各自的根
        

        while(edgenum < n){
            auto edge = edges.top();
            edges.pop();
            int x = edge.x;
            int y = edge.y;
            int val = edge.distfromstart;

            if(uf.find(x) != uf.find(y)){
                uf.union_(x, y);
                edgenum++;
                ans +=val;
                if(edgenum == n-1) break;
            }
        }

        return ans;

    }

    struct state{
        int x;
        int y;
        int distfromstart;
        state(int distfromstart,int x, int y) {
            this->x = x;
            this->y = y;
            this->distfromstart = distfromstart;
        }
        
        bool operator>(const state& other) const{
            return distfromstart > other.distfromstart;
        }
    };
};

//TC:O(n^2) SC:O(n) 原本會是o(n^2) 如果有用PQ所以變成多lgn
class Solution {   
    // prim
    int visited[1000];
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size();
        if(n==1) return 0;

        //prim 從某點出發開始不斷找最近的點 在把該點加入mst 再繼續比較更近的點  
        vector<int> mindist(n, INT_MAX);//一個mst 會不斷更新最近點的關係式
        mindist[0] = 0;
        int ans = 0;

        for(int k = 0; k<n; k++){//遍歷所有城市找距離目前mst最短的城市
            int gmin = INT_MAX;
            int next;
            for(int j = 0; j<n;j++){
                if(visited[j] == 0 && mindist[j] < gmin){//所有點都能抵達 找最短的
                    gmin = mindist[j];
                    next = j;
                }
            }
            visited[next] = 1;
            ans += mindist[next];

            //加入城市進入mst後 更新跟每個點最短距離
            for(int i = 0 ; i<n; i++){
                if(visited[i] == 0){
                    mindist[i] = min(mindist[i],abs(points[next][0] - points[i][0])+abs(points[next][1] - points[i][1]));
                }
            }
        }

        return ans;

    }
};


/*
解法2：Prim
Prim算法通常的复杂度也是ElogV，本题就是o(N^2logN)。
Prim的基本思想是，MST从节点0开始生长。MST里面只有节点0时，从所有节点0出发的边里面挑一个最短的，这时MST里就有两个点。
第二步是从这两个点所出发的所有边里面挑一个最短的，如果对应的第三点是已经访问过的，那就换下一个最短边，直到能确定第三个点。依次继续，直至确定N个点，则MST构建完成。
同理，priority_queue的模板类尽量避免用vector。

解法3：Prim, o(N^2)
在特殊情况下，Prim有o(N^2)的实现，那就是可以用邻接表来表示任意的边。这样对于稠密图而言，Prim的这种实现在时间上会有优势。

本题是个完全图，任意两点之间都有边，所以是可以有o(N^2)的实现，具体方法是：我们在构建MST的过程中收入了一个新点k，此时收录的点集是{q}. 
查看所有未被收入的点pi到k点的距离，用来更新di，其中di就是pi到距离点集{q}最小的长度。这样我们就可以在{di}找到最小的那个，对应的点就是下一次要收入的新点k'. 
因此这样的算法就不要使用priority_queue.
*/

// 10/18 kruskal 
class Solution {
    struct state{
        int dist;
        int x;
        int y;
        state(int dist, int x, int y){
            this->dist = dist;
            this->x = x;
            this->y = y;
        }
        bool operator>(const state& other) const{
            return dist > other.dist;
        }
    };
    int parent[1000];
    int find_(int x){
        if(x != parent[x]){
            parent[x] = find_(parent[x]);
        }
        return parent[x];
    }
    void Union_(int x,int y){
        x = find_(x);
        y = find_(y);
        if( x > y){
            parent[x] = y;
        }
        else if(x < y) parent[y] = x;
    }
public:
    int minCostConnectPoints(vector<vector<int>>& points) {
        // kruskal 將所有edge距離排序好 取最小值 但不能取到已經連結過的點的edge
        priority_queue<state, vector<state>, greater<state>> pq;
        int n = points.size();
        if(n==1) return 0;
        for(int i =0; i<n; i++){
            parent[i] = i;
        }

        for(int i=0; i<n; i++){
            for(int j = i+1; j<n; j++){
                pq.push({abs(points[i][0]-points[j][0])+abs(points[i][1]-points[j][1]),i,j});
            }
        }

        //開始建樹
        int count = 0;//edge數目
        int res = 0;//總共花費
        while(!pq.empty()){
            int a = pq.top().x;
            int b = pq.top().y;
            int dist = pq.top().dist;
            pq.pop();
            if(find_(a) != find_(b)) {
                Union_(a,b);
                count++;
                res+=dist;
            }
            
            if(count == n-1) return res;//最多就是n-1條
        }   
        return -1;
    }
};
