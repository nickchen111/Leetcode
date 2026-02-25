class Solution {
public:
    vector<int> sortByBits(vector<int>& arr) {
        auto cmp = [&](int a, int b) {
            int ca = popcount((uint32_t)a);
            int cb = popcount((uint32_t)b);
            return ca == cb ? a < b : ca < cb;
        };
        sort(arr.begin(), arr.end(), cmp);
        return arr;
    }
};