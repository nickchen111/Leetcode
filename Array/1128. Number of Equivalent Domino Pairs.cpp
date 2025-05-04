// TC:O(n) SC:O(n)
struct pair_hash {
    size_t operator()(const pair<int,int>& p) const {
        return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1);
    }
};

class Solution {
public:
    int numEquivDominoPairs(vector<vector<int>>& dominoes) {
        unordered_map<pair<int,int>, int, pair_hash> cnt;
        int ans = 0;
        for (auto& d : dominoes) {
            int a = min(d[0], d[1]);
            int b = max(d[0], d[1]);
            cnt[{a, b}]++;
            ans += cnt[{a,b}] - 1;
        }
        return ans;
    }
};
