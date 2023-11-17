/*
962. Maximum Width Ramp
*/


// TC:O(n) SC:O(n)
class Solution {
public:
    int maxWidthRamp(vector<int>& nums) {
        int n = nums.size();
        stack<int> s;
        for(int i = 0; i<n; i++){
            if(s.empty() || nums[s.top()] > nums[i]){
                s.push(i);
            }
        }
        int res=0;
        for(int i =n-1; i>=0; i--){
            while(!s.empty() && nums[s.top()] <= nums[i]){
                res = max(res, i-s.top());
                s.pop();
            }
        }

        return res;
    }
};
