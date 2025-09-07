// TC:O(n) SC:O(1)
class Solution {
public:
    int minOperations(string s) {
        int n = s.size();
        char ch = 'z' + 1;
        for (auto &x : s) {
            if (x != 'a') ch = min(ch, x);
        }
        return 'z' + 1 - ch;
    }
};
