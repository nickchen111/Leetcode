// TC:O(n) SC:O(1)
class Solution {
public:
    int maxProduct(int n) {
        string s = to_string(n);
        int m = s.size();
        int mx = 0, mx2 = 0;
        for (int i = 0; i < m; i++) {
            if (mx <= s[i] - '0') {
                mx2 = mx;
                mx = s[i] - '0';
            } else if (mx2 < s[i] - '0') {
                mx2 = s[i] - '0';
            }
        }
        return mx * mx2;
    }
};
