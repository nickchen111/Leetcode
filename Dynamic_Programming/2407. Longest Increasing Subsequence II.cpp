// TC:O(nlgU) U為nums最大值 SC:O(U)
class Solution {
public:
    int lengthOfLIS(vector<int>& nums, int k) {
        int u = *max_element(nums.begin(), nums.end());
        vector<int> mx(4*u);
        auto modify = [&](auto && modify, int o, int l, int r, int idx, int val) -> void {
            if(l == r) {
                mx[o] = val;
                return;
            }
            int mid = (l+r) / 2;
            if(idx <= mid) modify(modify,o*2, l, mid, idx, val);
            else modify(modify,o*2+1, mid+1, r, idx, val);
            mx[o] = max(mx[o*2+1], mx[o*2]);
        };
        auto query = [&](auto && query, int o, int l, int r, int L, int R) -> int {
            if(L <= l && r <= R) {
                return mx[o];
            }
            int mid = (l+r) / 2;
            int ans = 0;
            if(L <= mid) ans = query(query, o*2, l, mid, L, R);
            if(R > mid) ans = max(ans, query(query, o*2+1, mid+1, r, L, R));
            return ans;
        };

        int n = nums.size();
        for(int i = 0; i < n; i++) {
            if(nums[i] == 1) {
                modify(modify,1, 1, u, 1, 1);
            }
            else {
                int ans = 1 + query(query, 1, 1, u, max(1, nums[i] - k), nums[i] - 1);
                modify(modify, 1, 1, u, nums[i], ans);
            }
        }
        return mx[1];
    }
};

/*
這題要從 n^2 角度出發 只學貪心+二分解 那個思路無法解這題
f[i][j] 以前i個數，選擇j為結尾元素可以組成的最長數組是多少
if j != nums[i]: f[i][j] = f[i-1][j]
if j == nums[i]: f[i][j] = 1 + max(f[i-1][j'])  j - k <= j'
然後因為會發現說每次都是在求一個區間MAX，並且做單點修改
所以想到線段樹


*/
