/*
1347. Minimum Number of Steps to Make Two Strings Anagram
*/


// TC:O(n) SC:O(n)
class Solution {
public:
    int minSteps(string s, string t) {
        unordered_map<int,int> map;
        for(int i = 0; i < s.size(); i++){
            map[s[i]-'a'] += 1;
        }
        for(auto ch : t){
            map[ch-'a'] -= 1;
        }

        int res = 0;
        for(auto x : map){
            if(x.second < 0) res += (-x.second);
        }

        return res;
    }
};
