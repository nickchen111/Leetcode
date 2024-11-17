/*
3356. Zero Array Transformation II
*/

// TC:O((n + m)lgm) SC:O(n)
class Solution {
    using LL = long long;
public:
    int minZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size();
        int m = queries.size();

        auto check = [&](int mid) {
            vector<LL> diff(n + 1, 0);
            
            for (int i = 0; i < mid; i++) {
                int l = queries[i][0], r = queries[i][1], val = queries[i][2];
                diff[l] -= val;
                if (r + 1 < n) diff[r + 1] += val;
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
        };

        int left = 0, right = m;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (check(mid)) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }

        if (check(left)) return left;
        return -1;
    }
};


/*
 [2,0,2], queries = [[0,2,1],[0,2,1],[1,1,3]]
 -1 0 0 1
 -2 0 0 2
 -2 -3 3

*/
