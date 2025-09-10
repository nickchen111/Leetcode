// TC:O(nm + mf) SC:O(nm + f)
class Solution {
public:
    int minimumTeachings(int n, vector<vector<int>>& languages, vector<vector<int>>& friendships) {
        int m = languages.size();
        unordered_map<int, unordered_set<int>> u2l;
        for (int i = 0; i < m; i++) {
            for (int lang : languages[i]) {
                u2l[i].insert(lang);
            }
        }

        vector<pair<int,int>> n2c;
        for (auto &f : friendships) {
            int u1 = f[0] - 1, u2 = f[1] - 1;
            bool can = false;
            for (int l1 : u2l[u1]) {
                if (u2l[u2].count(l1)) {
                    can = true;
                    break;
                }
            }
            if (!can) n2c.push_back({u1, u2});
        }

        if (n2c.empty()) return 0;

        int ans = INT_MAX;
        for (int lang = 1; lang <= n; lang++) {
            unordered_set<int> need; 
            for (auto &[u1, u2] : n2c) {
                if (!u2l[u1].count(lang)) need.insert(u1);
                if (!u2l[u2].count(lang)) need.insert(u2);
            }
            ans = min(ans, (int)need.size());
        }
        return ans;
    }
};
