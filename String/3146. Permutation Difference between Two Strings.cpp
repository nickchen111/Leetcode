/*
3146. Permutation Difference between Two Strings
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int findPermutationDifference(string s, string t) {
        int n = s.size();
        int res = 0;
        unordered_map<int,int> map1;
        unordered_map<int,int> map2;
        for(int i = 0; i < n; i++){
            map1[s[i]-'a'] = i;
        }
        
        for(int i = 0; i < n; i++){
            map2[t[i]-'a'] = i;
        }
        
        for(int i = 0; i < n; i++){
            res += abs(map1[s[i]-'a'] - map2[s[i]-'a']);
        }
        
        return res;
    }
};
