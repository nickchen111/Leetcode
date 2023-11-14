/*
383. Ransom Note
*/

// TC:O(m+n) SC:O(m)
class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        unordered_map<char,int> map;
        for(auto ch:ransomNote){
            map[ch]+=1;
        }
        for(auto ch:magazine){
            map[ch]-=1;
        }
        for(auto x:map){
            if(x.second > 0) return false;
        }
        return true;
    }
};
