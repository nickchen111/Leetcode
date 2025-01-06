// TC: O(n^3 + n^2 * ⍺(n)) SC:O(n)
class Solution {
public:
    int numSimilarGroups(vector<string>& strs) {
        int n = strs.size();
        vector<int> parent(n);
        iota(parent.begin(), parent.end(), 0);
        auto find = [&](int x) -> int {
            int rt = x;
            while(rt != parent[rt]) rt = parent[rt];
            if(x != rt) parent[x] = rt;
            return rt;
        };
        auto union_ = [&](int x, int y) -> void {
            x = find(x), y = find(y);
            if(x < y) parent[y] = x;
            else parent[x] = y;
        };

        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j < n; j++) {
                int cnt = 0;
                int p1 = 0, p2 = 0;
                while(p1 < strs[i].size()) {
                    if(strs[i][p1] != strs[j][p2]) {
                        cnt += 1;
                    }
                    p1 += 1;
                    p2 += 1;
                    if(cnt > 2) break;
                }
                if(cnt < 3) {
                    union_(i, j);
                }
            }
        }

        unordered_set<int> set;
        for(int i = 0; i < n; i++) {
            set.insert(find(i));
        }
        return (int)set.size();
    }
};
