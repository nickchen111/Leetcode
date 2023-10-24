/*
130. Surrounded Regions
*/

//此題想求圈圈叉叉內 如果有圈圈四面八方都被插插包圓 就把圈圈改成叉叉 如果是靠近邊緣的圈圈這種被包圍就不算
//從外面一圈檢查 有無圈圈 有的話bfs他 標記他所有可以走到的圈圈 標為 ＃ 然後在最後把他們改回圈圈 其餘沒被標成＃改成叉叉
// BFS TC:O(m*n*(m+n)) SC:O(m*n)
class Solution {
    int m,n;
public:
    void solve(vector<vector<char>>& board) {
        //BFS
        m = board.size(); n = board[0].size();
        for(int i = 0; i<m; i++){
            if(board[i][0] == 'O') BFS(board,i,0);
            if(board[i][n-1] == 'O') BFS(board,i,n-1);
        }
        for(int j = 0; j<n; j++){
            if(board[0][j] == 'O') BFS(board,0,j);
            if(board[m-1][j] == 'O') BFS(board,m-1,j);
        }

        for(int i = 0; i<m; i++){
            for(int j = 0; j<n; j++){
                if(board[i][j] == 'O') board[i][j] = 'X';
                else if(board[i][j] == '#') board[i][j] = 'O';
            }
        }
    }

    vector<int> dirs = {0,1,0,-1,0};
    void BFS(vector<vector<char>>& board, int x, int y){
        board[x][y] = '#';
        queue<pair<int,int>> q;
        q.push({x,y});
        while(!q.empty()){
            int i = q.front().first;
            int j = q.front().second;
            q.pop();

            for(int t =1; t<dirs.size(); t++){
                int nx = i+dirs[t-1];
                int ny =j+dirs[t];
                if(nx<0 || ny<0 || nx>=m || ny>=n || board[nx][ny] == 'X' || board[nx][ny] == '#') continue;
                q.push({nx,ny});
                board[nx][ny] = '#';
            }
        }
    }
};

// DFS TC:O(m*n*(m+n)) SC:O(m*n)
class Solution {
public:
    void solve(vector<vector<char>>& board) {
        int M = board.size();
        if(M == 0) return;
        int N= board[0].size();

        for(int i = 0;  i < M; i++){
            if(board[i][0] == 'O') dfs(board, i, 0);
            if(board[i][N-1] =='O') dfs(board, i, N-1);
        }
        for(int j = 0;  j < N; j++){
            if(board[0][j] == 'O') dfs(board, 0, j);
            if(board[M-1][j] =='O') dfs(board, M-1, j);
        }
        for (int i=0; i<M; i++)
            for (int j=0; j<N; j++){
                if(board[i][j] == '#') board[i][j] = 'O';
                else if(board[i][j] == 'O') board[i][j] = 'X';
            }
 
    }
    void dfs(vector<vector<char>>& board, int i, int j){
        vector<pair<int, int>> dir = {{0,1}, {0,-1}, {1,0},{-1,0}};
        int M = board.size();
        int N= board[0].size();

        //前序位置
        if(i < 0 || j < 0 || i >=M || j >=N) return;

        if(board[i][j] == 'O'){
            board[i][j] = '#';
            dfs(board,i+1,j);
            dfs(board,i,j+1);
            dfs(board,i-1,j);
            dfs(board,i,j-1);
        }
        else if(board[i][j] == 'X' || board[i][j] == '#') return;
    }
