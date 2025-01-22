/*
395. Longest Substring with At Least K Repeating Characters
*/

// 2025.01.22
class Solution {
public:
    int longestSubstring(string s, int k) {
        int n = s.size();
        int ans = 0;
        for(int len = 26; len >= 1; len--) {
            vector<int> cnt(26);
            int valid = 0, i = 0, ch = 0;
            for(int j = 0; j < n; j++) {
                cnt[s[j] - 'a'] += 1;
                if(cnt[s[j] - 'a'] == k) valid += 1;
                if(cnt[s[j] - 'a'] == 1) ch += 1;
                while(ch > len) {
                    if(cnt[s[i] - 'a'] == k) valid -= 1;
                    if(cnt[s[i] - 'a'] == 1) ch -= 1;
                    cnt[s[i] - 'a'] -= 1;
                    i += 1;
                }
                if(valid == ch) ans = max(ans, j - i + 1);
            }
        }

        return ans;
    }
};

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
