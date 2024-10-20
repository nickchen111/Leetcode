/*
3325. Count Substrings With K-Frequency Characters I
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int numberOfSubstrings(string s, int k) {
        int n = s.size();
        unordered_map<char, int> map;
        int i = 0;
        bool flag = false;
        int res = 0;
        int j = 0;
        for(int i = 0; i < n; i++) {
            while(j < n && flag == 0) {
                map[s[j]] += 1;
                if(map[s[j]] == k) flag = 1;
                j++;
            }
            
            if(flag) res += (n-j+1);
            map[s[i]] -= 1;
            if(map[s[i]] == k-1) flag = 0;
        }
        
        return res;
    }
};
