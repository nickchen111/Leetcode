// TC:O(n) SC:O(1)
class Solution {
    typedef long long LL;
    LL MOD = 1e9 + 7;
public:
    int countHomogenous(string s) {
        int n = s.size(), i = 0;
        LL ans = 0;
        while(i < n) {
            int start = i;
            while(i + 1 < n && s[i+1] == s[i]) i += 1;
            ans = (ans + (LL)(i - start + 1) * (1 + i - start + 1) / 2) % MOD;
            i += 1;
        }
        return ans;
    }
};
