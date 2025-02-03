// TC:O(n^2 * 2 * (m)) m 為字串平均長度 SC:O(1)
class Solution {
public:
    int findLUSlength(vector<string>& strs) {
        int n = strs.size();
        int ans = -1;
        for(int i = 0; i < n; i++) {
            bool flag = true;
            for(int j = 0; j < n; j++) {
                if(i == j) continue;
                int p1 = 0, p2 = 0, m = strs[i].size(), k = strs[j].size();
                if(m > k) continue;
                while(p1 < m && p2 < k) {
                    if(strs[i][p1] == strs[j][p2]) {
                        p1 += 1, p2 += 1;
                    }
                    else p2 += 1;
                }
                if(p1 == m) {
                    flag = false;
                    break;
                }
            }
            if(flag) ans = max(ans, (int)strs[i].size());
        }
        return ans;
    }
};
