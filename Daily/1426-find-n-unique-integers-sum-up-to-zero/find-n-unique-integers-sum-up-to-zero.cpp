class Solution {
public:
    vector<int> sumZero(int n) {
        vector<int> ans;
        if (n % 2) {
            ans.emplace_back(0);
            n -= 1;
        }
        if (n) {
            int start = n / 2;
            for (int i = -start; i <= start; i++) {
                if (i == 0) continue;
                ans.emplace_back(i);
            }
        }
        return ans;
    }
};