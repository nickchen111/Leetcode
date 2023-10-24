/*
79. Word Search
*/

// DFS TC:O(m*n*4^L) SC:O(m*N+L) L 是單詞長度
class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size(); int n = board[0].size();
        vector<bool> visited(m*n+1);

        //每點都可能是起點
        for(int i = 0; i < m; i++){
            for(int j = 0; j <n; j++){
                if(DFS(board, word, i, j,0, visited)) return true;
            }
        }

        return false;
    }

    vector<int> dirs = {0,1,0,-1,0};
    bool DFS(vector<vector<char>>& board, string word, int x, int y, int count, vector<bool>& visited){
        if(count == word.size()){
            return true;
        }

        int m = board.size(); int n = board[0].size();

        if(x < 0 || y < 0 || x>=m || y >=n || visited[x*n+y] == true) return false;

        if(board[x][y] != word[count]) return false;

        visited[x*n+y] = true;
        for(int i = 1; i<dirs.size(); i++){
            int nx = x + dirs[i-1];
            int ny = y + dirs[i];
            if(DFS(board, word, nx,ny,count+1,visited)) return true;
        }
        visited[x*n+y] = false;

        return false;
    }
};
