// TC:O(n(lgn + k^2)) SC:O(n* k^2)
class Solution {
    using LL = long long;
public:
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();
        struct Interval { int l, r, weight, i; };
        vector<Interval> arr;
        for(int i = 0; i < n; i++) {
            arr.push_back({intervals[i][0], intervals[i][1], intervals[i][2], i});
        }
        auto cmp = [](const Interval& a, const Interval& b) {
            return a.r < b.r;
        };
        sort(arr.begin(), arr.end(), cmp);
        
        vector<array<pair<LL, vector<int>>, 5>> dp(n+1);
        auto cmp2 = [](const Interval& a, const Interval& b) {
            return a.r < b.l;
        };
        for(int i = 0; i < n; i++) {
            auto [l, r, weight, idx] = arr[i];
            int k = lower_bound(arr.begin(), arr.begin() + i, Interval{l, INT_MAX, INT_MAX, INT_MAX}, cmp2) - arr.begin();
            for(int j = 1; j < 5; j++) {
                LL s1 = dp[i][j].first;
                LL s2 = dp[k][j-1].first + weight;
                if(s1 > s2) {
                    dp[i+1][j] = dp[i][j];
                    continue;
                }
                vector<int> new_id = dp[k][j-1].second;
                new_id.push_back(idx);
                sort(new_id.begin(), new_id.end());
                if(s1 == s2 && new_id > dp[i][j].second) {
                    new_id = dp[i][j].second;
                }
                dp[i+1][j] = {s2, new_id};
            }
        }
        
        return dp[n][4].second;
        
    }
};
