class Solution {
public:
    int maximumWhiteTiles(vector<vector<int>>& tiles, int carpetLen) {
        sort(tiles.begin(), tiles.end());
        // 前綴和 + 二分 TC:O(nlgn) SC:O(n)
        int n = tiles.size();
        vector<int> presum(n+1); 
        map<int,int> map; // r -> index for presum
        map[0] = 0;
        unordered_map<int,int> r2l; // r -> l
        for(int i = 0; i < n; i++) {
            map[tiles[i][1]] = i+1;
            r2l[tiles[i][1]] = tiles[i][0];
            presum[i+1] = presum[i] + tiles[i][1] - tiles[i][0] + 1;
        }

        int ans = 0;
        auto query = [&](int l, int r) -> int {
            int sum = presum[map[r]];
            auto iter = map.lower_bound(r - carpetLen + 1);
            if(iter == map.begin()) return sum;
            iter = prev(iter);
            sum -= presum[iter->second];
            iter = next(iter);
            if(r2l[iter->first] < r - carpetLen + 1) {
                sum -= r - carpetLen + 1 - r2l[iter->first];
            }

            return sum;
        };
        for(auto &tile : tiles) {
            int l = tile[0], r = tile[1];
            ans = max(ans, query(l,r));
        }

        return ans;
        /*
        Sliding Window TC:O(n + nlgn) SC:O(n)
        int ans = 0, left = 0, cover = 0;
        for(auto &tile : tiles) {
            int l = tile[0], r = tile[1];
            // 右邊進
            cover += r - l + 1;
            // 左邊出
            while(tiles[left][1] < r - carpetLen + 1) {
                cover -= tiles[left][1] - tiles[left][0] + 1;
                left += 1;
            }
            // 更新結果
            int uncover = max(r - carpetLen + 1 - tiles[left][0], 0);
            ans = max(ans, cover - uncover);
        }

        return ans;
        */
    }
};
