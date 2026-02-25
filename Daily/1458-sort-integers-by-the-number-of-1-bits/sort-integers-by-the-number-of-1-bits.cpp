class Solution {
public:
    vector<int> sortByBits(vector<int>& arr) {
        auto cmp = [&](int a, int b) {
            int ca = __builtin_popcount(a);
            int cb = __builtin_popcount(b);
            return ca == cb ? a < b : ca < cb;
        };
        sort(arr.begin(), arr.end(), cmp);
        return arr;
    }
};