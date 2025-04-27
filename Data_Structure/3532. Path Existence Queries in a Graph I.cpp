// TC:O(n * ⍺(n) + m) SC:O(n) 此題也可以二分
class Solution {
public:
    vector<bool> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        /*
        看來就是只要兩個點距離不超過maxDiff就可以uf再一起
        */
        vector<int> pa(n);
        iota(pa.begin(), pa.end(), 0);
        
        vector<int> idx(n);
        iota(idx.begin(), idx.end(), 0);
        auto find = [&](int x) -> int {
            while (x != pa[x]) {
                pa[x] = pa[pa[x]]; 
                x = pa[x];
            }
            return x;
        };
        
        auto merge = [&](int x, int y) -> void {
            x = find(x), y = find(y);
            if (x < y) {
                pa[y] = x;
            } 
            else pa[x] = y;
        };
        
        for (int i = 1; i < n; i++) {
            int curr_idx = idx[i];
            int prev_idx = idx[i-1];
            if (abs(nums[curr_idx] - nums[prev_idx]) <= maxDiff) {
                merge(curr_idx, prev_idx);
            }
        }
        
        vector<bool> ans;
        for (auto &q : queries) {
            int a = q[0], b = q[1];
            if (find(a) == find(b)) {
                ans.emplace_back(true);
            }
            else ans.emplace_back(false);
        }
        return ans;
     }
};
