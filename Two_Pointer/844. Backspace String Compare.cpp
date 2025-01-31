// TC:O(n + m) SC:O(1)
class Solution {
public:
    bool backspaceCompare(string s, string t) {
        int cnt1 = 0, cnt2 = 0, i = s.size() - 1, j = t.size() - 1;
        while(i >= 0 || j >= 0) {
            while(i >= 0) {
                if(s[i] == '#') cnt1 += 1;
                else if(cnt1) cnt1 -= 1;
                else break;
                i--;
            }
            
            while(j >= 0) {
                if(t[j] == '#') cnt2 += 1;
                else if(cnt2) cnt2 -= 1;
                else break;
                j--;
            }
            
            if(i >= 0 && j >= 0) {
                if(s[i] == t[j]) {
                    i --, j --;
                }
                else return false;
            }
            else if(i >= 0 || j >= 0) return false;
        }
        return i < 0 && j < 0;
    }
};
