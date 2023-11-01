/*
209. Minimum Size Subarray Sum
*/

//Deque TC: O(n) SC:O(n)
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        //deque
        deque<int> dq;
        int sum = 0;

        int res = INT_MAX/2;
        for(int i =0; i<nums.size(); i++){
            dq.push_back(i);
            sum+=nums[i];
            while(!dq.empty() && sum >= target){
                res = min(res, i-dq.front()+1);
                sum-=nums[dq.front()];
                dq.pop_front();
            }
        }

        return res == INT_MAX/2 ? 0:res;
           
    }
};

// Slide Window TC: O(n) SC:O(1)
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        // slide window
        int sum = 0;
        int res = INT_MAX/2;
        int left = 0;
        int right = 0;
        int n = nums.size();
        while(right < n){
            //開始擴大窗口
            sum+=nums[right];

            //縮小窗口
            while(left < n && sum >= target){
                res = min(res, right-left+1);
                sum-=nums[left];
                left++;
            }
            right++;
        }

        return res == INT_MAX/2 ? 0:res;
    }
};
