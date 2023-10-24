/*
209. Minimum Size Subarray Sum
*/

// slide window TC: O(n) sc:O(1)
class Solution {
    // slide window
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int sum = 0;
        int res = INT_MAX;
        int count = 0;

        int left = 0; int right = 0;
        while(right < nums.size()){
            //擴大窗口
            sum+=nums[right];
            count++;
            right++;
            //縮小窗口
            while(sum >= target){
                res = min(res, count);
                sum-=nums[left];
                left++;
                count--;
            }
        }

        return res == INT_MAX ? 0:res;
    }
};

/*
感覺slide window 
presum都可以解
*/
