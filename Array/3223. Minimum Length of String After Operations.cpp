/*
3223. Minimum Length of String After Operations
*/

// TC:O(n) SC:O(26)
class Solution {
public:
    int minimumLength(string s) {
        int n = s.size();
        unordered_map<char,int> map;
        for(auto x : s){
            map[x] += 1;
        }
        
        int res =0;
        for(auto &[ch, freq] : map){
            if(freq % 2 == 0) res += 2;
            else res += 1;
        }
        
        return res;
    }
};
