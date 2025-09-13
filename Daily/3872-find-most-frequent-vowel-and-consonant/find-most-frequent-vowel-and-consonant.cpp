class Solution {
public:
    int maxFreqSum(string s) {
        unordered_set<char> st = {'a', 'e', 'i', 'o', 'u'};
        int mx = 0, mx2 = 0;
        unordered_map<char,int> mp1, mp2;
        for (auto &ch : s) {
            if (st.count(ch)) {
                mp1[ch] += 1;
                mx = max(mx, mp1[ch]);
            }
            else {
                mp2[ch] += 1;
                mx2 = max(mx2, mp2[ch]);
            }
        }
        return mx + mx2;
    }
};