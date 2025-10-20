class Solution {
public:
    int finalValueAfterOperations(vector<string>& operations) {
        int ans = 0;
        for (auto &op : operations) {
            if (op[0] == '-' || op[2] == '-') ans -= 1;
            else ans += 1;
        }
        return ans;
    }
};