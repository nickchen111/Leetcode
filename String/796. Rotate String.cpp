/*
796. Rotate String
*/

// TC:O(m + n) SC:O(m + n)
class Solution {
public:
    bool rotateString(string s, string goal) {
        int n = s.size(); 
        int m = goal.size();
        if(n != m) return false;
        s = s + s;
        // z function 先算出自己的狀況
        n = s.size();
        auto cal_z = [&](string& goal) -> vector<int> {
            vector<int> z(m);
            z[0] = m;
            for(int i = 1, c = 1, r = 1, len; i < m; i++) {
                len = r > i ? min(z[i-c], r-i) : 0;
                while(i + len < m && goal[i] == goal[i+len]) {
                    len++;
                }
                if(i + len > r) {
                    c = i;
                    r = i + len;
                }
                z[i] = len;
            }

            return z;
        };

        vector<int> z = cal_z(goal);
        
        auto cal_e = [&](string& t, string& s) -> bool {
            vector<int> e(n);
            for(int i = 0, r = 0, c = 0, len; i < n; i++) {
                len = r > i ? min(z[i-c], r-i) : 0;
                while(i + len < n && s[i+len] == t[len]) {
                    len++;
                }
                if(i + len > r) {
                    c = i;
                    r = i + len;
                }
                e[i] = len;
                if(e[i] == (int)t.size()) return true;
                if(i > n/2+1) return false;
            }

            return false;
        };

        return cal_e(goal, s);
    }
};
