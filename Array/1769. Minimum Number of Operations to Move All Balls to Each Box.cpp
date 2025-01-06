// TC:O(n) SC:O(1)
class Solution {
public:
    vector<int> minOperations(string s) {
        int n = s.size();
        int prefix = 0;
        int ans = 0;
        vector<int> res(n);
        for(int i = 0; i < n; i++) {
            ans += prefix;
            if(s[i] == '1') prefix += 1;
        }
        res.back() = ans;
        int suffix = s.back() == '1';
        prefix -= (s.back() == '1');
        for(int i = n-2; i >= 0; i--) {
            ans = ans - prefix + suffix;
            res[i] = ans;
            if(s[i] == '1'){
                prefix -= 1;
                suffix += 1;
            }
        }

        return res;
    }
};
