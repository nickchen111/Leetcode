/*
791. Custom Sort String
*/

// TC:O(n+m) SC:O(n)
class Solution {
public:
    string customSortString(string order, string s) {
        unordered_map<int,int> map;
        string ret;
        for(auto x : s){
            map[x] += 1;
        }

        for(int i = 0; i < order.size(); i++){
            if(map.find(order[i]) != map.end()){
                while(map[order[i]]){
                    ret += order[i];
                    map[order[i]] -= 1;
                }
            }
        }
        for(auto x : s){
            if(map[x]){
                ret += x;
            }
        }

        return ret;
    }
};
