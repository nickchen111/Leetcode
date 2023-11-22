/*
713. Subarray Product Less Than K
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        // slide window
        int sum = 1;
        int res = 0;
        int j = 0;
        for(int i = 0; i<nums.size(); i++){
            if(j < i){
                j = i;
                sum = 1;
            }
            while(j < nums.size() && sum*nums[j] < k){
                sum*=nums[j];
                j++;
            }
            res+=(j-i);
            sum/=nums[i];
        }

        return res < 0 ? 0:res;
    }
};
/*
此題考點要乘法的特殊性導致如果找不到數字低於k的話 sum = 0 之後就都會錯 並且ｊ的位置也會在i前面
*/
