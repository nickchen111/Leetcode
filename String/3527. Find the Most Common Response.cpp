// TC:O(n * m * L) m為每個組裡的字串數量, L 為字串平均長度 SC:O(n * m * L)
class Solution {
public:
    string findCommonResponse(vector<vector<string>>& responses) {
        unordered_map<string, int> mp;
        for (auto & res:responses) {
            unordered_set<string> st(res.begin(), res.end());
            for (auto & s : st) {
                mp[s] += 1;
            }
        }
        string ans;
        int mxF = 0;
        for (auto &[s, cnt] : mp) {
            if (cnt > mxF) {
                mxF = cnt;
                ans = s;
            }
            else if (cnt == mxF) {
                ans = min(ans, s);
            }
        }
        return ans;
    }
};
