/*
3365. Rearrange K Substrings to Form Target String
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    bool isPossibleToRearrange(string s, string t, int k) {
        int n = s.size();
        int len = n / k;
        unordered_map<string, int> map;
        for(int i = 0; i < n; i+=len) {
            map[s.substr(i, len)] += 1;
        }
        
        for(int i = 0; i < n; i+=len) {
            string tmp = t.substr(i, len);
            if(map.find(tmp) != map.end()) {
                map[tmp] -= 1;
                if(map[tmp] == 0) map.erase(tmp);
            }
            else return false;
        }
        return true;
    }
};
