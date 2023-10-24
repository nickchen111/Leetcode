/*
130. Surrounded Regions
*/
//使用union find去解這題島嶼問題 
//用dfs bfs更快

void solve(vector<vector<char>>& board) {
    if(board.empty()) return;

    int m = board.size();
    int n = board[0].size();

    //给dummy留一个额外位置
    UF uf(m*n+1);//引用UF类
    int dummy = m*n;
    //将首列和末列的O与dummy相连
    for (int i = 0; i < m; i++) {
        if (board[i][0] == 'O') {
            uf._union(i * n, dummy);
        }
        if (board[i][n - 1] == 'O') {
            uf._union(i * n + n - 1, dummy);
        }
    }

    //将首行和末行的O与dummy相连
    for (int j = 0; j < n; j++) {
        if (board[0][j] == 'O') {
            uf._union(j, dummy);
        }
        if (board[m - 1][j] == 'O') {
            uf._union(n * (m - 1) + j, dummy);
        }
    }

    //方向数组 d 是上下左右搜索的常用手法
    int d[4][2] = {{1,0}, {0,1}, {0,-1}, {-1,0}};
    for (int i = 1; i < m - 1; i++) {
        for (int j = 1; j < n - 1; j++) {
            if (board[i][j] == 'O') {
                //将此 O 与上下左右的 O 相连
                for (int k = 0; k < 4; k++) {
                    int x = i + d[k][0];
                    int y = j + d[k][1];

                    if (board[x][y] == 'O') {
                        uf._union(x * n + y, i * n + j);
                    }
                }
            }
        }
    }

    //所有不和dummy相连的O，都要被替换
    for (int i = 1; i < m - 1; i++) {
        for (int j = 1; j < n - 1; j++) {
            if(!uf.isConnected(dummy, i*n+j)) {
                board[i][j] = 'X';
            }
        }
    }
}

//標準  uf寫法 手刻
class UF {
    vector<int> parent;
public:
    UF(int n) {
        for (int i = 0; i < n; i++) {
            parent.push_back(i);
        }
    }

    int find(int x) {
        if(x!=parent[x]) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void _union(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if(rootX!=rootY) {
            parent[rootX] = rootY;
        }
    }

    bool isConnected(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        return rootX==rootY;
    }
};

/*
解題思維：
你可以把那些不需要被替换的 O 看成一个拥有独门绝技的门派，它们有一个共同「祖师爷」叫 dummy，这些 O 和 dummy 互相连通，而那些需要被替换的 O 与 dummy 不连通。
这就是 Union-Find 的核心思路，明白这个图，就很容易看懂代码了。

首先要解决的是，根据我们的实现，Union-Find 底层用的是一维数组，构造函数需要传入这个数组的大小，而题目给的是一个二维棋盘。

这个很简单，二维坐标 (x,y) 可以转换成 x * n + y 这个数（m 是棋盘的行数，n 是棋盘的列数），敲黑板，这是将二维坐标映射到一维的常用技巧。

其次，我们之前描述的「祖师爷」是虚构的，需要给他老人家留个位置。索引 [0.. m*n-1] 都是棋盘内坐标的一维映射，那就让这个虚拟的 dummy 节点占据索引 m * n 好了。
*/
