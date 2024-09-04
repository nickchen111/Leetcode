/*
874. Walking Robot Simulation
*/

// TC:O(n*m) SC:O(k)
class Solution {
public:
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        unordered_map<int, unordered_set<int>> map;
        for(auto o : obstacles){
            map[o[0]].insert(o[1]);
        }

        int res = 0;
        int n = commands.size();
        int dirx = 0, diry = 1;
        int x = 0, y = 0;
        for(int i = 0; i < n; i++){
            if(commands[i] == -1){
                if(dirx == 0 && diry == 1) {
                    dirx = 1;
                    diry = 0;
                }
                else if(dirx == 0 && diry == -1){
                    dirx = -1;
                    diry = 0;
                }
                else if(dirx == 1 && diry == 0){
                    dirx = 0;
                    diry = -1;
                }
                else if(dirx == -1 && diry == 0){
                    dirx = 0;
                    diry = 1;
                }
                continue;
            }
            else if(commands[i] == -2){
                if(dirx == 0 && diry == 1) {
                    dirx = -1;
                    diry = 0;
                }
                else if(dirx == 0 && diry == -1){
                    dirx = 1;
                    diry = 0;
                }
                else if(dirx == 1 && diry == 0){
                    dirx = 0;
                    diry = 1;
                }
                else if(dirx == -1 && diry == 0){
                    dirx = 0;
                    diry = -1;
                }
                continue;
            }
            else {
                int curx = x;
                int cury = y;
                for(int j = 0; j < commands[i]; j++){
                    curx += dirx;
                    cury += diry;
                    if(map[curx].find(cury) != map[curx].end()){
                        break;
                    }
                    x = curx;
                    y = cury;
                    res = max(res, x*x+y*y);
                }
            }
        }
        
        return res;
    }
};
