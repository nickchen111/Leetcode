// TC:O(n^2 * lgU) SC:O(1)
class Solution {
    int gcd(int a, int b) {
        if(b == 0) return a;
        return gcd(b, a % b);
    }
    
    int lcm(int a, int b) {
        return (long long)a * b / gcd(a, b);
    }
public:
    int maxLength(vector<int>& nums) {
        int n = nums.size();
        int res = 0;
        int all_lcm = 1;
        for(auto &num : nums) all_lcm = lcm(all_lcm, num);
        for(int i = 0; i < n; i++) {
            int prod = 1;
            int g = 0;
            int l = 1;
            
            for(int j = i; j < n; j++) {
                prod = prod * nums[j];
                g = gcd(g, nums[j]);
                l = lcm(l, nums[j]);
                if(prod > all_lcm * g) break;
                if(prod == g * l) {
                    res = max(res, j - i + 1);
                }
            }
        }
        return res;
    }
};
