// TC:O(n*m)  m 是陣列所有字串的字數總和 SC:O(1)
class Solution {
public:
    int expressiveWords(string s, vector<string>& words) {
        int n = s.size(), ans = 0;
        
        for (string &word : words) {
            int m = word.size(), i = 0, j = 0;
            bool ok = true;
            
            while (ok && i < n && j < m) {
                if(s[i] != word[j]) {
                    ok = false;
                    break;
                }
                int a = i, b = j;
                while(a < n && s[a] == s[i]) a++;
                while(b < m && word[b] == word[j]) b++;
                int len_s = a - i, len_w = b - j;
                if(len_s != len_w && (len_w > len_s || len_s < 3)) ok = false;
                i = a, j = b;
            }
            ans += (ok && i == n && j == m);
        }
        return ans;
    }
};
