// TC:O(nm) SC:O(nm)
class Solution {
    using ll = long long;
public:
    long long countPairs(vector<string>& words) {
        ll ans = 0;
        unordered_map<string, ll> mp;
        for (auto &word : words) {
            string s = "a";
            int time = (26 - (word[0] - 'a')) % 26;
            int n = word.size();
            for (int i = 1; i < n; i++) {
                s += (word[i] - 'a' + time) % 26 + 'a';
            }
            ans += mp[s];
            mp[s] += 1;
        }
        return ans;
    }
};
