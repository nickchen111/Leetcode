// TC:O(n * m) m 為數字長度 SC:O(1)
class Solution {
public:
    int smallestIndex(vector<int>& nums) {
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            int x = nums[i];
            int sum = 0;
            while (x) {
                sum += x % 10;
                x /= 10;
            }
            if (sum == i) {
                return i;
            }
        }
        return -1;
    }
};
