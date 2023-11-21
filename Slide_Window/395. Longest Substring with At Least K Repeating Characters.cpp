/*
395. Longest Substring with At Least K Repeating Characters
*/

// TC:O(26*n) SC:O(26)
class Solution {
public:
    int longestSubstring(string s, int k) {
        int n = s.size();
        int res = 0;
        for(int m = 1; m<=26; m++){
            res = max(res, helper(s,m,k));
        }

        return res;
    }
    int helper(string& s, int m, int k){
        unordered_map<char,int> map;
        int count = 0;
        int j = 0;
        int res = 0;
        for(int i =0; i<s.size(); i++){
            while(j < s.size() && map.size() <=m){
                map[s[j]]+=1;
                if(map[s[j]] == k) count++;
                if(map.size() == m && count == m) res = max(res,j-i+1);
                j++;
            }
            map[s[i]]--;
            if(map[s[i]] == k-1) count-=1;
            //這裡要注意清空key 才不會多算種類
            if(map[s[i]] == 0) map.erase(s[i]);
        }

        return res;
    }
};
