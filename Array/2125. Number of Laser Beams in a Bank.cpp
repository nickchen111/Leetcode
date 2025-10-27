// TC:O(m * n) SC:O(1)
class Solution {
public:
    int numberOfBeams(vector<string>& bank) {
        int prev = 0, ans = 0;
        for (auto &s : bank) {
            int tmp = 0;
            for (auto &ch : s) {
                if (ch == '1') tmp += 1;
            }
            ans += tmp * prev;
            if(tmp) prev = tmp;
        }
        return ans;
    }
};
