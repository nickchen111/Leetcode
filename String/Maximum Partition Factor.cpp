// TC:O(n) SC:O(1)
class Solution {
public:
    bool scoreBalance(string s) {
        int total = 0;
        for (auto &ch : s) {
            total += ch - 'a' + 1;
        }
        if (total % 2) return false;
        int cur = 0;
        for (auto &ch : s) {
            cur += ch - 'a' + 1;
            if (cur == total / 2) return true;
        }
        return false;
    }
};
