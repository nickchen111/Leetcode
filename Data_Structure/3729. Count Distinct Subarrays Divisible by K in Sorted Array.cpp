// TC:O(n) SC:O(n)
class Solution {
public:
    long long numGoodSubarrays(vector<int>& nums, int k) {
        int s = 0;
        long long ans = 0;
        unordered_map<int, int> cnt, cnt_s;
        for (int x : nums) {
            cnt_s[s]++;
            s = (s + x) % k;
            ans += cnt_s[s];
            cnt[x]++;
        }

        for (auto [x, c] : cnt)
            for (long long l = 1; l <= c; l++)
                if ((x * l) % k == 0)
                    ans -= c - l;

        return ans;
    }
};
