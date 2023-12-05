/*
1496. Path Crossing
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    bool isPathCrossing(string path) {
        set<pair<int,int>> set;
        set.insert({0,0});
        pair<int,int> cur = {0,0};
        int n = path.size();
        for(int i = 0; i < n; i++){
            if(path[i] == 'N'){
                cur.second+=1;
                if(set.find(cur) != set.end()) return true;
                set.insert(cur);
            }
            else if(path[i] == 'E'){
                cur.first+=1;
                if(set.find(cur) != set.end()) return true;
                set.insert(cur);
            }
            else if(path[i] == 'S'){
                cur.second-=1;
                if(set.find(cur) != set.end()) return true;
                set.insert(cur);
            }
            else if(path[i] == 'W'){
                cur.first-=1;
                if(set.find(cur) != set.end()) return true;
                set.insert(cur);
            }
        }

        return false;
    }
};
