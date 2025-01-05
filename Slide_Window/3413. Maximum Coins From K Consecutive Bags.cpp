class Solution {
    using LL = long long;
public:
    long long maximumCoins(vector<vector<int>>& coins, int k) {
        sort(coins.begin(), coins.end());
        // 前綴和 + 二分 TC:O(nlgn) SC:O(n)
        int n = coins.size();
        vector<LL> presum(n+1);
        map<LL, LL> map; // r -> index
        map[0] = 0;
        unordered_map<LL, pair<LL, LL>> r2l;
        unordered_map<LL, pair<LL, LL>> l2r;
        for(int i = 0; i < n; i++) {
            presum[i+1] = presum[i] + (LL)(coins[i][1] - coins[i][0] + 1) * coins[i][2];
            map[coins[i][1]] = i + 1;
            r2l[coins[i][1]] = {coins[i][0], coins[i][2]};
            l2r[coins[i][0]] = {coins[i][1], coins[i][2]};
        }
        LL res = 0;
        auto query = [&](int l, int r) -> LL {
            // 計算右邊端點狀況
            LL cand1 = presum[map[r]];
            auto iter = map.lower_bound(r - k + 1);
            if(iter != map.begin()) {
                iter = prev(iter);
                cand1 -= presum[iter->second];
                iter = next(iter);
                if(r2l[iter->first].first <= r - k + 1) {
                    cand1 -= (LL)(r - k + 1 - r2l[iter->first].first) * r2l[iter->first].second;
                }
            }
            LL cand2 = 0;
            iter = map.upper_bound(l + k - 1); // 大於當下的r
            iter = prev(iter);
            cand2 = presum[iter->second] - presum[map[r]-1];
            iter = next(iter);
            if(iter != map.end()) {
                if(r2l[iter->first].first <= l + k - 1) {
                    cand2 += (LL)(l + k - 1 - r2l[iter->first].first + 1) * r2l[iter->first].second;
                }
            }

            return max(cand2, cand1);

        };
        for(auto &coin : coins) {
            int l = coin[0], r = coin[1];
            res = max(res, query(l,r));
        }

        return res;
        /*
        Sliding Window TC:O(n + nlgn) SC:O(n)
        auto solve = [&](vector<vector<int>>& coins) -> LL {
            LL ans = 0, cover = 0, left = 0;
            for(auto &coin : coins) {
                LL l = coin[0], r = coin[1], weight = coin[2];
                // 右邊進
                cover += (LL)(r - l + 1) * weight;
                // 左邊出
                while(coins[left][1] < r - k + 1) {
                    cover -= (LL)(coins[left][1] - coins[left][0] + 1) * coins[left][2];
                    left += 1;
                }
                LL uncover = max(0LL, (LL) (r - k + 1 - coins[left][0]) * coins[left][2]);
                ans = max(ans, cover - uncover);
            }

            return ans;
        };
        LL res = solve(coins);
        // 改成左端點 往右延伸看能到哪 只要reverse 然後再將數值交換改成複數就可以複用function...
        reverse(coins.begin(), coins.end()); 
        for(auto &coin : coins) {
            int tmp = coin[0];
            coin[0] = -coin[1];
            coin[1] = -tmp;
        }

        return max(res, solve(coins));
        */
    }
};

