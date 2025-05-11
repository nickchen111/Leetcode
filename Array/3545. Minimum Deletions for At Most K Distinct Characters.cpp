// TC:O(n + m + mlgm) SC:O(n + m)
class Solution {
public:
    int minDeletion(string s, int k) {
        int n = s.size();
        unordered_map<char, int> mp;
        for (auto &ch : s) {
            mp[ch] += 1;
        }
        
        if (mp.size() <= k) return 0;
        vector<int> freq;
        for (auto [ch, f] : mp) {
            freq.push_back(f);
        }
        sort(freq.begin(), freq.end());
        
        int to_remove = mp.size() - k;
        int ans = 0;
        
        for (int i = 0; i < to_remove; i++) {
            ans += freq[i];
        }
        
        return ans;
    }
};
