/*
2914. Minimum Number of Changes to Make Binary String Beautiful
*/

// TC:O(n/2) SC:O(1)
class Solution {
public:
    int minChanges(string s) {
        int n = s.size();
        int res = 0;
        for(int i = 0; i < n; i+=2) {
            if(s[i] != s[i+1]) {
                res += 1;
            }
        }

        return res;
    }
};


// TC:(n) SC:O(1)
class Solution {
public:
    int minChanges(string s) {
        int n = s.size();
        int cnt0 = 0;
        int cnt1 = 0;
        int res = 0;
        for(int i = 0; i < n; i++) {
            cnt0 += s[i] == '0';
            cnt1 += s[i] != '0';
            if(i%2) {
                res += min(cnt0, cnt1);
                cnt0 = 0;
                cnt1 = 0;
            }
        }

        return res;
    }
};
