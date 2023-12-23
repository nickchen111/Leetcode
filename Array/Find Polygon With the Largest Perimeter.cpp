/*
Find Polygon With the Largest Perimeter
*/

// TC:O(nlgn+n) SC:O(n)
class Solution {
    using LL = long long;
public:
    long long largestPerimeter(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int n = nums.size();
        vector<LL> presum(n+1);
        presum[0] = 0;
        for(int i = 1; i <= n; i++){
            presum[i] = presum[i-1] + nums[i-1];
        }
        
        //貪心的找最大的那項看能否當作前面點的最長邊 至少有三面
        LL res = -1;
        for(int i = n-1; i >= 2; i--){
            int target = nums[i];
            if(target < presum[i]){
                res = presum[i+1];
                break;
            }
        }
        
        return res;
    }
};
