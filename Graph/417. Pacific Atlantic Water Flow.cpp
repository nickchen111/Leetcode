/*
417. Pacific Atlantic Water Flow
對於此種網格類的題目 然後他又給你這種和邊界上的節點有關係 都可以換種角度思考 例如可從邊界出發
*/


//此題說明為想問 點可以從高處流向低處 或者跟他一樣高的點 求哪些點可以符合留到左邊或者上面的太平洋以及右邊或下面的大西洋 兩者同時符合才行
// 10/17
class Solution {
    int m, n;
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        //對兩個邊界都去做看看DFS各自收集可以走到的元素
        m = heights.size(); n = heights[0].size();
        vector<vector<bool>> P(m, vector<bool>(n,0));
        vector<vector<bool>> A(m, vector<bool>(n,0));
        for(int i = 0; i<m; i++){
            DFS(heights,0,i,0,P);
            DFS(heights,0,i,n-1,A);
        }
        for(int j = 0; j<n; j++){
            DFS(heights,0,0,j,P);
            DFS(heights,0,m-1,j,A);
        }

        vector<vector<int>> res;
        for(int i = 0; i<m; i++){
            for(int j = 0; j<n; j++){
                if(P[i][j] && A[i][j]){
                    res.push_back({i,j});
                }
            }
        }

        return res;
    }

    vector<int> dirs = {0,1,0,-1,0};
    void DFS(vector<vector<int>>& heights, int h,int x, int y, vector<vector<bool>>& v){
        if(h > heights[x][y]) return;
        v[x][y] = true;
        for(int i =1; i<dirs.size(); i++){
            int nx = x+dirs[i-1];
            int ny = y+dirs[i];
            if(nx<0 || ny<0 || nx>=m || ny>=n) continue;
            if(v[nx][ny] == true) continue;
            DFS(heights,heights[x][y],nx,ny,v);
        }
    }
};



//DFS TC:O(2*(m+n) + mn) SC:O(2*mn)
class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        if(heights.empty()) return {};
        int m = heights.size();
        int n = heights[0].size();
        //可標記為看過的空間初始化
        vector<vector<int>> p(m, vector<int>(n)); //通往太平洋 這寫法可同時初始化外圈跟內圈的空間大小
        vector<vector<int>> a(m, vector<int>(n));//通往大西洋
        //開始遍歷外圍邊邊node去做dfs
        for(int y=0;y< m;y++){
            dfs(heights, 0, 0, y, p); // h那項為上個元素的高度
            dfs(heights, 0,n-1, y, a);
        }
        for(int x=0;x<n;x++){
            dfs(heights, 0,x,0,p);
            dfs(heights, 0,x,m-1,a);
        }
        vector<vector<int>> ans;
        for(int y=0; y<m; y++){
            for(int x=0; x<n; x++){
                if(p[y][x] && a[y][x]){
                    ans.push_back({y,x}); //也可以用emplace_back 可以直接在括號內構造型態 ans.emplace_back(vector<int>{y,x});
                }
            }
        }
        return ans;

    }
    void dfs(vector<vector<int>>& b ,int h, int x, int y, vector<vector<int>>& v){
        if(x < 0 || y < 0 || x >= b[0].size() || y >= b.size()) return;
        if(v[y][x] || b[y][x] < h) return;
        v[y][x] = true;
        dfs(b, b[y][x], x+1, y, v);
        dfs(b, b[y][x], x-1, y, v);
        dfs(b, b[y][x], x, y+1, v);
        dfs(b, b[y][x], x, y-1, v);
    }
};


//BFS TC:O(2*(m+n) + mn) SC:O(4*mn)
class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        if(heights.empty()) return {};
        //標記為看過的空間
        int m = heights.size();
        int n = heights[0].size();
        vector<vector<int>> va(m, vector<int>(n, 0));
        vector<vector<int>> vb(m, vector<int>(n, 0));
        queue<pair<int, int>> qa;
        queue<pair<int, int>> qb;
        int h;
        //開始搜尋邊邊bfs
        for(int y=0; y < m; y++){
            qa.push({y, 0});
            qb.push({y,n-1});
        }
        for(int x=0; x < n; x++){
            qa.push({0, x});
            qb.push({m-1,x});
        }
        bfs(heights, h, va, qa);
        bfs(heights, h, vb, qb);
        vector<vector<int>> ans; //答案儲存空間

        //開始找哪些是兩個都可以抵達的
        for(int y=0; y < m; y++){
            for(int x=0; x < n; x++){
                if(va[y][x] != 0 && vb[y][x] != 0){
                    ans.push_back({y,x});
                }
            }
        }
        return ans;
    }
        //bfs狀況分析
        void bfs(vector<vector<int>>& b, int h, vector<vector<int>>& v, queue<pair<int, int>>& q){
            int m = b.size(); 
            int n = b[0].size();
            while(!q.empty()){
                vector<int> dir = {1,0,-1,0,1};
                int dx[4] = {-1,0,1,0};
                int dy[4] = {0,1,0,-1};
                int y = q.front().first;
                int x = q.front().second;
                h = b[y][x];
                q.pop();
                if(v[y][x]) continue;
                v[y][x] = 1;

                for(int i = 0; i < 4; i++){
                    int tx = x + dir[i];
                    int ty = y + dir[i+1];
                    if(tx < 0 || ty < 0 || tx >= n || ty >= m || b[ty][tx] < h) continue;
                    if(v[ty][tx]) continue;
                    q.push({ty,tx});
                }
            }
        }
};

/*
解題思路
1.只去bfs邊邊的node  分成兩個海洋的邊邊node 遍歷完 要標記為已看過
2.可以連通到邊邊node的所有點標記成可以
3.兩邊做完後如果都可以到兩個海洋的座標加到ans裡面
*/
