/*
1579. Remove Max Number of Edges to Keep Graph Fully Traversable
*/


// 2025.01.08
class Solution {
public:
    int maxNumEdgesToRemove(int n, vector<vector<int>>& edges) {
        vector<vector<int>> Alice;
        vector<vector<int>> Bob;
        vector<int> pa(n+1);
        iota(pa.begin(), pa.end(), 0);
        vector<int> rank(n+1,1);
        auto find = [&](int x, vector<int>& pa) -> int {
            int rt = x;
            while(rt != pa[rt]) rt = pa[rt];
            if(x != rt) pa[x] = rt;
            return rt;
        };
        auto union_ = [&](int x,int y, vector<int>& pa, vector<int>& rank) -> void {
            x = find(x,pa), y = find(y,pa);
            if(rank[x] < rank[y]) pa[x] = y;
            else {
                pa[y] = x;
                if(rank[x] == rank[y]) rank[x] += 1;
            }
        };
        int cnt = 0;
        for(auto &edge:edges) {
            if(edge[0] == 1) Alice.push_back(edge);
            else if(edge[0] == 2) Bob.push_back(edge);
            else {
                if(find(edge[1], pa) != find(edge[2], pa)) union_(edge[1], edge[2], pa, rank);
                else cnt += 1;
            }
        }
        
        auto solve = [&](vector<vector<int>>& connect, vector<int>& pa, vector<int>& rank) -> int {
            int cnt = 0;
            for(auto &c : connect) {
                if(find(c[1],pa) != find(c[2],pa)) {
                    union_(c[1], c[2], pa, rank);
                }
                else cnt += 1;
            }
            unordered_set<int> set;
            for(int i = 1; i <= n; i++) {
                set.insert(find(i, pa));
            }
            return (int)set.size() > 1 ? -1 : cnt;
        };
        vector<int> pa1 = pa;
        vector<int> rank1 = rank;
        int cand1 = solve(Alice, pa1, rank1);
        if(cand1 == -1) return -1;
        int cand2 = solve(Bob, pa, rank);
        if(cand2 == -1) return -1;
        return cand2 + cand1 + cnt;
    }
};

/*
我的想法是做兩次UF 然後判斷誰的砍掉路徑最少
1. Alice 接收 1,3 type, Bob 接收 2, 3 type
2. 優先創建3的路線 如果發現3路徑超過n-1條 直接return total - (n-1)
3. 接著就要思考如何選取剩下的線 當發現加了這個線的狀況 無法讓兩邊連接起來 就跳過不加入
*/

// TC:O(n) SC:O(n)
class Solution {
    int parent[100005];
    int parent0[100005]; // for bob
    int find(int x){
        if(x != parent[x]){
            parent[x] = find(parent[x]);
        }

        return parent[x];
    }
    void union_(int x, int y){
        x = find(x);
        y = find(y);
        if(x > y) parent[x] = y;
        else parent[y] = x;
    }
public:
    int maxNumEdgesToRemove(int n, vector<vector<int>>& edges) {
        for(int i = 0; i < n; i++){
            parent[i] = i;
        }

        int count0 = 0, count1 = 0, count2 = 0;
        vector<vector<int>> edge1;
        vector<vector<int>> edge2;
        for(auto edge : edges){
            int a = edge[1];
            int b = edge[2];
            if(edge[0] == 3){
                if(find(a) != find(b)){
                    union_(a, b);
                    count0 += 1;
                }
            }
            else if(edge[0] == 1){
                edge1.push_back({a,b});
                edge1.push_back({b,a});
            }
            else {
                edge2.push_back({a,b});
                edge2.push_back({b,a});
            }
        }

        memcpy(parent0, parent, sizeof(parent));// dest source, size

        for(auto edge : edge1){
            int a = edge[0];
            int b = edge[1]; 
            if(find(a) != find(b)){
                union_(a, b);
                count1 += 1;
            }
        }
        if(count0 + count1 < n-1) return -1;
        memcpy(parent, parent0, sizeof(parent));
        for(auto edge : edge2){
            int a = edge[0];
            int b = edge[1];
            if(find(a) != find(b)){
                union_(a, b);
                count2 += 1;
            }
        }

        if(count0 + count2 < n-1) return -1;

        return (int)edges.size() - count0 - count1 - count2;
    }
};
