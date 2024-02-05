/*
387. First Unique Character in a String
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int firstUniqChar(string s) {
        int res = INT_MAX;
        unordered_map<char, vector<int>> map;
        for(int i = 0; i < s.size(); i++){
            map[s[i]].push_back(i);
        }

        for(auto p : map){
            if(p.second.size() == 1) {
                res = min(res, p.second[0]);
            }
        }

        return res == INT_MAX ?  -1 : res;
    }
};
