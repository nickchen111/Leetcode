// TC:O(nlgn) SC:O(n)
class Solution {
    using ll = long long;
public:
    int minimumPairRemoval(vector<int>& nums) {
        int n = nums.size();
        set<pair<ll, int>> pairs; // 相差與idx
        set<ll> idx;
        int desc = 0;
        for (int i = 0; i < n - 1; i ++) {
            pairs.insert({nums[i+1] + nums[i], i});
            if (nums[i + 1] < nums[i]) desc += 1;
            idx.insert(i);
        }
        idx.insert(n-1);
        vector<long long> a(nums.begin(), nums.end());
        int ans = 0;
        while (desc) {
            ans += 1;
            auto [s, i] = *pairs.begin();
            pairs.erase(pairs.begin());
            
            auto it = idx.lower_bound(i);
            auto nxt_it = next(it);
            int nxt = *nxt_it;
            desc -= a[i] > a[nxt];
            if (it != idx.begin()) {
                int pre = *prev(it); // 上一個index
                desc -= a[pre] > a[i];
                desc += a[pre] > s;
                pairs.erase({a[pre] + a[i], pre});
                pairs.emplace(a[pre] + s, pre);
            }
            auto nxt_it2 = next(nxt_it);
            if (nxt_it2 != idx.end()) {
                // 先開始算desc
                int nxt2 = *nxt_it2;
                desc -= a[nxt] > a[nxt2];
                desc +=  s > a[nxt2];
                pairs.erase({a[nxt] + a[nxt2], nxt});
                pairs.emplace(a[nxt2] + s, i);
            }
            
            a[i] = s;
            idx.erase(nxt);
        }
        
        return ans;
        
    }
};
