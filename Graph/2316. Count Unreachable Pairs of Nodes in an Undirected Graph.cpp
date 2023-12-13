/*
2316. Count Unreachable Pairs of Nodes in an Undirected Graph
*/

// Union Find O(V+E) SC:O(N + E)
class Solution {
    class UF{
        vector<int> parent;
    public:
        UF(int n){
            for(int i = 0;  i < n; i++){
                parent.push_back(i);
            }
        }
        int find(int x){
            if(parent[x] != x){
                parent[x] = find(parent[x]);
            }

            return parent[x];
        }
        void union_(int x,int y){
            int rootx = find(x);
            int rooty = find(y);
            //小的當根
            if(rootx > rooty){
                parent[rootx] = rooty;
            }
            else if(rootx < rooty){
                parent[rooty] = rootx;
            }
        }
    };
public:
    long long countPairs(int n, vector<vector<int>>& edges) {
        UF uf(n);

        for(auto edge: edges){
            int a = edge[0], b = edge[1];
            if(uf.find(a) != uf.find(b)){
                uf.union_(a,b);
            }
        }

        
        unordered_map<int,int> map;
        for(int i = n-1; i >= 0; i--){
            int cur = uf.find(i);
            map[cur] += 1;

        }
        // 4 1 2
        long long res = 0;
        
        for(auto p:map){
            res += (long long)(p.second) * (n - p.second);
        }

        res /= 2;
        return res;
    }
};

// BFS O(V+E) SC:O(N + E)
class Solution {
public:
    long long countPairs(int n, vector<vector<int>>& edges) {
        long long res = 0;
        
        vector<vector<int>> graph(n);
        for(auto edge:edges){
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
        }

        if(edges.size() == 0){
            return (long long)n*(n-1)/2;
        }
        vector<bool> visited(n,0);
        vector<int> arr;
        for(int i = 0; i < n; i++){
            if(visited[i] == 1) continue;
            queue<int> q;
            q.push(i);
            int count = 0;
            while(!q.empty()){
                int cur = q.front();
                q.pop();
                if(visited[cur] == 1) continue;
                visited[cur] = 1;
                count++;
                for(auto neighbor : graph[cur]){
                    if(visited[neighbor] == 1) continue;
                    q.push(neighbor);
                }
            }
            arr.push_back(count);
        }

        for(int i = 0; i < arr.size(); i++){
            res += (long long)arr[i] * (n - arr[i]);
        }

        res /= 2;

        return res;
    }
};

/*
此題想問說 有哪幾組點到點之間是沒路可以相通的
4 + 2 + 4*2 = 14
如果能把它一組一組綑綁起來算出個數然後用乘法就會比較簡單了 -> n^2 太慢
此題不論是用DFS BFS Union 藉由計算連通分量公式最快 N - Connected V 就會某點跟其他點沒有相連的個數
*/
