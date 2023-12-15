/*
1436. Destination City
*/

// TC:O(2*n) SC:O(n)
class Solution {
public:
    string destCity(vector<vector<string>>& paths) {
        unordered_map<string, int> map;
        for(auto path : paths){
            map[path[0]] += 1;
            map[path[1]] += 0;
        }
        
        for(auto p:map){
            if(p.second == 0) return p.first;
        }

        return "";
    }
};

/*
此題就是要找出度為0的city
我都去把抵達點紀錄起來 然後順便去刪掉如果出發點有在我的集合裡剩下的就是答案
*/
