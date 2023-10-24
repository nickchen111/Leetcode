/*
242. Valid Anagram
*/

// TC:O(n)  SC:O(n)
class Solution {
public:
    bool isAnagram(string s, string t) {
        unordered_map<char,int> map;
        int n = s.size();
        int m = t.size();
        if(m != n) return false;
        for(int i = 0; i<s.size(); i++){
            map[s[i]]++;
        }

        for(int i = 0; i<t.size(); i++){
            map[t[i]]--;
        }

        for(int i = 0; i<map.size(); i++){
            if(map[i] != 0) return false;
        }

        return true;
    }
};
