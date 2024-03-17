/*
3083. Existence of a Substring in a String and Its Reverse
*/

// TC:O(n) SC:O(n/2)
class Solution {
public:
    bool isSubstringPresent(string s) {
        int n = s.size();
        if(n == 1) return false;
        unordered_set<string> set;
        for(int i = 0; i+1 < n; i++){
            string cur = s.substr(i,2);
            set.insert(cur);
        }
        reverse(s.begin(), s.end());
        for(int i = 0; i+1 < n; i++){
            string cur = s.substr(i,2);
            if(set.find(cur) != set.end()) return true;
        }
        
        return false;
    }
};
