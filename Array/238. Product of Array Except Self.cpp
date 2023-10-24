/*
238. Product of Array Except Self
*/


// TC:O(n) SC:O(n)
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        //從前後各遍歷一次求出答案
        //空間換時間
        int  n = nums.size();
        vector<int> presum(n,1);
        vector<int> suffsum(n,1);
        for(int i = 1; i < n; i++){
            presum[i] = presum[i-1]*nums[i-1];
        }
        for(int i = n-2; i>=0; i--){
            suffsum[i] = suffsum[i+1]*nums[i+1];
        }

        vector<int> res;
        for(int i = 0; i<n;i++){
            res.push_back(presum[i]*suffsum[i]);
        }
        
        return res;
    }
};
