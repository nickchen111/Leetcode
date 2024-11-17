/*
3355. Zero Array Transformation I
*/

// TC:O(n + m) SC:O(n)
class Solution {
    using LL = long long;
public:
    bool isZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        int m = queries.size();
        vector<LL> diff(n + 1, 0);
        for (int i = 0; i < m; i++) {
            int l = queries[i][0], r = queries[i][1];
            diff[l] -= 1;
            if (r + 1 < n) diff[r + 1] += 1;
        }

        LL sum = 0;
        vector<LL> temp(nums.begin(), nums.end());

        for (int i = 0; i < n; i++) {
            sum += diff[i];
            temp[i] += sum;
        }

        for (int i = 0; i < n; i++) {
            if (temp[i] > 0) return false;
        }

        return true;
    }
};
