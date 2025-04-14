// TC:O(n * n + n * lgn) SC:O(n)
class Solution {
public:
    int countGoodTriplets(vector<int>& arr, int a, int b, int c) {
        int n = arr.size();
        int ans = 0;

        multiset<int> left;
        multiset<int> right(arr.begin() + 1, arr.end());

        for (int j = 1; j < n - 1; ++j) {
            left.insert(arr[j - 1]);
            right.erase(right.find(arr[j]));

            int mid = arr[j];
            // 找出 right 中在 [mid - b, mid + b] 範圍的元素
            auto low = right.lower_bound(mid - b);
            auto high = right.upper_bound(mid + b);

            vector<int> right_valid(low, high);
            int m = right_valid.size();

            // 找出 left 中在 [mid - a, mid + a] 範圍的元素
            auto l_low = left.lower_bound(mid - a);
            auto l_high = left.upper_bound(mid + a);

            for (auto i_val = l_low; i_val != l_high; ++i_val) {
                int k_start = 0, k_end = 0;
                while (k_start < m && right_valid[k_start] < *i_val - c) ++k_start;
                while (k_end < m && right_valid[k_end] <= *i_val + c) ++k_end;
                ans += (k_end - k_start);
            }
        }

        return ans;
    }
};
