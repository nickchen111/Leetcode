// TC:O((n + q) lgn) SC:O(nlgn)
class Solution {
    // static constexpr int MAXLOG = 17; // 2^17 = 131072 > 1e5
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        vector<int> idx(n);
        iota(idx.begin(), idx.end(), 0);
        ranges::sort(idx, [&](const int i, const int j) { return nums[i] < nums[j];});
        vector<int> map_idx(n); // 原本的index 現在到哪個位置 因為他是給你原本的index 需要mapping一下
        for (int i = 0; i < n; i++) {
            map_idx[idx[i]] = i;
        }
        ranges::sort(nums);
        int MAXLOG = bit_width(unsigned(n));
        // 計算跳一步最遠能跳去哪
        vector<int> r(n);
        for (int i = 0, j = 0; i < n; i++) {
            while (j + 1 < n && nums[j+1] - nums[i] <= maxDiff) j++;
            r[i] = j;
        }
        // 建立倍增表 f
        // static int f[100000][MAXLOG+1];
        vector<vector<int>> f(n, vector<int>(MAXLOG+1)); 
        // k=0
        for (int i = 0; i < n; i++) {
            f[i][0] = r[i];
        }
        // k>=1
        for (int k = 1; k <= MAXLOG; k++) {
            for (int i = 0; i < n; i++) {
                f[i][k] = f[ f[i][k-1]] [k-1];
            }
        }

        vector<int> ans;
        for (auto &q : queries) {
            int u = q[0], v = q[1];
            int su = min(map_idx[u],map_idx[v]) , sv = max(map_idx[u],map_idx[v]);
            if (su == sv) {
                ans.push_back(0);
                continue;
            }
            if (f[su][MAXLOG] < sv) {
                ans.push_back(-1);
                continue;
            }
            int curr = su, steps = 0;
            for (int k = MAXLOG; k >= 0; k--) {
                if (f[curr][k] < sv) {
                    steps += (1 << k);
                    curr = f[curr][k];
                }
            }
            ans.push_back(steps + 1);
        }
        return ans;
    }
};

