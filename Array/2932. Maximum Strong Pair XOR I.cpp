/*
2932. Maximum Strong Pair XOR I
*/

// Bruete force TC:O(n^2) SC:O(1)
class Solution {
public:
    int maximumStrongPairXor(vector<int>& nums) {
        // XOR 相同為0不同為1
        //010 100-> 110=0->4+2=6 相加最大   0111 7 1010 10 -> 1101->13
        int res = 0;
        int n = nums.size();
        for(int i = 0; i<n; i++){
            for(int j = 1; j<n; j++){
                if(abs(nums[i]-nums[j]) <= min(nums[i],nums[j])){
                    res = max(res,nums[i]^nums[j]);
                }
            }
        }
        
        return res;
    }
};
