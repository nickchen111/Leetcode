// TC:O(n) SC:O(n)
class Solution {
public:
    int minimumFlips(int n) {
        string s;
        while (n) {
            s += n % 2 == 0 ? "0" : "1";
            n /= 2;
        } 

        string t = s;
        reverse(s.begin(), s.end());
        int ans = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] != t[i]) ans += 1;
        }
        return ans;
    }
};
