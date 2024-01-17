/*
1207. Unique Number of Occurrences
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    bool uniqueOccurrences(vector<int>& arr) {
        unordered_map<int,int> map;
        for(auto x : arr){
            map[x] += 1;
        }
        unordered_set<int> set;
        for(auto p : map){
            if(set.find(p.second) != set.end()) return false;
            set.insert(p.second);
        }
        return true;
    }
};
