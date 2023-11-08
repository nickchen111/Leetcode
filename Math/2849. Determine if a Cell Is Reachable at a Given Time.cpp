/*
2849. Determine if a Cell Is Reachable at a Given Time
*/

// TC:O(1) SC:O(1)
class Solution {
public:
    bool isReachableAtTime(int sx, int sy, int fx, int fy, int t) {
        int x = abs(sx-fx);
        int y = abs(sy-fy);
        if(x == 0 && y == 0 && t == 1) return false;
        return max(x,y)<=t;
    }
};

// DFS+Greedy TC:O(n) SC:O(n)->TLE 
class Solution {
    bool flag = false;
public:
    bool isReachableAtTime(int sx, int sy, int fx, int fy, int t) {
        if(sx == fx && sy == fy && t ==0) return true;
        DFS(sx,sy,fx,fy,t,0);
        return flag;
    }

    void DFS(int sx, int sy, int fx, int fy, int t,int count){
        if(sx == fx && sy == fy && count <= t && count != 0){
            flag = true;
            return;
        }
        if(count > t) {
            flag = false;
            return;
        }
        //對角線狀況考慮
        if(sx > fx && sy > fy){
            DFS(sx-1,sy-1,fx,fy,t,count+1);
            return;
        }
        else if(sx > fx && sy < fy){
            DFS(sx-1,sy+1,fx,fy,t,count+1);
            return;
        }
        else if(sx < fx && sy > fy){
            DFS(sx+1,sy-1,fx,fy,t,count+1);
            return;
        }
        else if(sx < fx && sy < fy){
            DFS(sx+1,sy+1,fx,fy,t,count+1);
            return;
        }
        else if(sx == fx && sy > fy){
            DFS(sx,sy-1,fx,fy,t,count+1);
            return;
        }
        else if(sx == fx && sy < fy){
            DFS(sx,sy+1,fx,fy,t,count+1);
            return;
        }
        else if(sx > fx && sy == fy){
            DFS(sx-1,sy,fx,fy,t,count+1);
            return;
        }
        else if(sx < fx && sy == fy){
            DFS(sx+1,sy,fx,fy,t,count+1);
            return;
        }
        else {
            DFS(sx+1,sy+1,fx,fy,t,count+1);
            return;
        }
    }
};
