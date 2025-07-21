class Solution {
public:
    string makeFancyString(string s) {
        int n = s.size();
        int i = 0;
        while (i < n) {
            int j = i + 1;
            while (j < n && s[j] == s[i] && j - i + 1 <= 2) {
                j += 1;
            }
            while (j < n && s[j] == s[i]) {
                s[j] = '#';
                j += 1;
            }
            i = j;
        }
        string ans;
        for(auto &ch : s) {
            if (ch != '#') ans += ch;
        }
        return ans;
    }
};