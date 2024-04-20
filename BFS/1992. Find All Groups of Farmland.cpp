/*
1992. Find All Groups of Farmland
*/


// TC:O(n) SC:O(n)
class Solution {
public:
    vector<vector<int>> findFarmland(vector<vector<int>>& land) {
        int m = land.size();
        int n = land[0].size();
        vector<vector<int>> res;
        vector<int> dirs = {1,0,1};
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                if(land[i][j] == 1){
                    queue<pair<int,int>> q;
                    int startx = i;
                    int starty = j;
                    int endx = -1;
                    int endy = -1;
                    vector<bool> visited(m*n+1);
                    q.push({i,j});
                    while(!q.empty()){
                        int sz = q.size();
                        while(sz--){
                            int curx = q.front().first;
                            int cury = q.front().second;
                            q.pop();
                            if(visited[curx*n+cury]) continue;
                            visited[curx*n+cury] = 1;
                            endx = curx;
                            endy = cury;
                            for(int k = 1; k < dirs.size(); k++){
                                int newx = curx + dirs[k-1];
                                int newy = cury + dirs[k];
                                if(newx < 0 || newy < 0 || newx >= m || newy >= n || visited[newx*n+newy] || land[newx][newy] == 0) continue;
                                land[newx][newy] = 0;
                                q.push({newx,newy});
                            }
                        }
                    }

                    if(endx != -1 && endy != -1){
                        res.push_back({startx,starty,endx,endy});
                    }
                    else {
                        res.push_back({startx,starty,startx,starty});
                    }
                }
            }
        }

        return res;
    }
};

/*
簡單來說就是找到所有獨立1組成的group左上右下點
*/
