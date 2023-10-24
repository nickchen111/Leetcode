/*
1584. Min Cost to Connect All Points
*/

class Solution {
    // kruskal algo
    class UF{
    public:
        int parent[1000];//為了節省時間
        int count;

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
        if(n == 1) return 0; // base case

        //用priority_queue就不用用sort排序來減少時間複雜度
        priority_queue<array<int, 3>, vector<array<int, 3>>, greater<array<int, 3>> > edges;
 

        for(int i = 0; i < n; i++){//城市i到
            for(int j = i+1; j < n; j++){//城市j
                int xi = points[i][0]; int yi = points[i][1];
                int xj = points[j][0]; int yj = points[j][1];
                edges.push({abs(xi-xj)+abs(yi-yj), i, j});
            }
        }

        int mstsum = 0;
        int edgenum = 0;
        UF uf(n);
        while(edgenum < n){
            auto edge = edges.top();// pq是用top
            edges.pop();
            int i = edge[1];
            int j = edge[2];
            int dis = edge[0];
     
            if(uf.find(i) != uf.find(j)){
                mstsum += dis;
                uf.union_(i, j);
                edgenum++;
                if(edgenum == n-1) break;//頂多只會有n-1條edge
            }
        }

        return mstsum;
    }
};


//hg大的krustal algo
class Solution {
    int parent[1000];
    
    int find(int x)
    {
        if (parent[x]!=x)
            parent[x] = find(parent[x]);
        return parent[x];
    }
    
    void Union(int x, int y)
    {
        int rootx = find(x);
        int rooty = find(y);
        if(rootx != rooty){
        parent[rootx] = rooty;
        }
        else return;
    }    
public:
    int minCostConnectPoints(vector<vector<int>>& points) 
    {
        int n = points.size();
        if(n == 1) return 0;
        for (int i=0; i<n; i++)
            parent[i] = i;
        
        priority_queue<array<int,3>, vector<array<int,3>>, greater<array<int,3>>>edges;
        for (int i=0; i<n; i++)
            for (int j=i+1; j<n; j++)
            {
                int xi = points[i][0]; int yi = points[i][1];
                int xj = points[j][0]; int yj = points[j][1];
                edges.push({abs(xi-xj)+abs(yi-yj), i, j});
            }
               
        int result = 0;
        int count = 0;
        while (count < n)
        {       
            auto edge = edges.top();
            edges.pop();
            int a = edge[1];
            int b = edge[2];
            int dis = edge[0];
            if (find(a)!=find(b))
            {
                Union(a,b);
                count++;
                result+=dis;
                if (count==n-1) break;
            }
        }
        
        return result;        
    }
};

// prim 
class Solution {   
    int visited[1000];
public:
    int minCostConnectPoints(vector<vector<int>>& points) 
    {
        int n = points.size();
        if(n == 1) return 0;
        vector<int>mindist(n, INT_MAX);
        mindist[0] = 0; //從0出發
        int ans = 0;

        for(int k = 0; k < n; k++){//traverse每個city
            int gmin = INT_MAX;
            int next;
            for(int j = 0; j < n; j++){
                if(visited[j] == 0 && mindist[j] <= gmin){
                    gmin = mindist[j];
                    next = j;
                }
            }
            visited[next] = 1;
            ans +=mindist[next];

            for(int j = 0; j < n; j++){
                if(visited[j] == 0){
                    int new_dist = abs(points[j][0] - points[next][0]) + abs(points[j][1] - points[next][1]);
                    mindist[j] = min(mindist[j], new_dist);//此時mindist就會去紀錄每個點到"當下"的生成樹的最小距離
                    // ex: 第一輪就會記住所有對於k=0 從0出發的點大家到他的距離 第二輪就會是1到大家的距離 有比0到大家更近的就會取代
                }
            }
        }    
        return ans;
    }
};

/*
經典最小生成樹問題 用kruskal or prim
kruskal: tc: o(ELGE) if E = N^2 就會是 n^2(lgn)偏大
1.不用vector<vector<int>> edge 裝 就可以不用sort 
改乘用priority queue 不看的時候不排序 要用的時候才會排第一個出來
2. 盡量不用vector 用array<int, 3> 3為定長
tc: o(ELGE) if E = N^2 就會是 n^2(lgn)偏大 sc: o(n^2) from priority queue n^2個邊

prim:
在特殊情况下，Prim有o( N^2)的实现，那就是可以用邻接表来表示任意的边。这样对于稠密图而言，Prim的这种实现在时间上会有优势。
這題就是此種案例 本题是个完全图，任意两点之间都有边，所以是可以有o(N^2)的实现
tc: o(n^2) sc:o(n)
*/
