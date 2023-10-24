/*
773. Sliding Puzzle
*/

//BFS TC:O(m*n) SC:O(m*n)
class Solution {
public:
    int slidingPuzzle(vector<vector<int>>& board) {
        int m = 2; int n = 3; 
        string target ="123450";
        string temp ="";
        for(int i = 0; i<m; i++){
            for(int j = 0; j<n; j++){
                temp+=to_string(board[i][j]);
            }
        }
        if(temp == target) return 0;

        queue<string> q;
        q.push(temp);

        unordered_set<string> visited;
        visited.insert(temp);

        vector<int> dirs = {0,1,0,-1,0};
        int step = 0;
        while(!q.empty()){
            int sz = q.size();
            for(int i = 0; i<sz; i++){
                string s = q.front();
                q.pop();
                if(target == s) return step;
                int idx;
                for(int j = 0; j<s.size(); j++){
                    if(s[j] == '0'){
                        idx = j;
                        break;
                    }
                }

                int x = idx/3;//轉換一維idex變成二維
                int y = idx%3;
                for(int k = 1; k<dirs.size(); k++){
                    int nx = x + dirs[k-1];
                    int ny = y + dirs[k];
                    if(nx<0 || ny<0 || nx>=m || ny>=n) continue;
                    int idx2 = nx*n+ny;
                    string t = s;
                    swap(t[idx],t[idx2]);// t[idx] = t[idx2]; t[idx2] = '0';
                    if(visited.find(t) != visited.end()) continue;
                    q.push(t);
                    visited.insert(t);
                }
            }
            step++;
        }
        return -1;
    }
};

/*
"此題為益智遊戲類題 窮舉出答案 算是考一些DS與string 操作的BFS考題
值得練看看"
*/
