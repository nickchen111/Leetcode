// TC:O(n) SC:O(1)
class Solution {
public:
    int maximumPossibleSize(vector<int>& nums) {
        /*
        每次可以將一個subarray替換成裡面最大的數字，問說最長的單調遞增數組為多長?
        n = 2 * 1e5 大概可以n lgn 感覺是在問LIS 錯了一發 感覺更像nextGreater 然後去走
        */
        int n = nums.size();
        int mx = -1;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if(nums[i] >= mx) {
                mx = nums[i];
                ans += 1;
            }
        }
        return ans;
        /*
        vector<int> nxtGreater(n, n);
        stack<int> stack;
        for (int i = n - 1; i >= 0; i--) {
            while (!stack.empty() && nums[i] > nums[stack.top()]) {
                stack.pop();
            }
            if(!stack.empty()) nxtGreater[i] = stack.top();
            stack.push(i);
        }
        int i = 0;
        int ans = 0;
        while(true) {
            if (i == n) break;
            ans += 1;
            i = nxtGreater[i];
        }
        return ans;
        */
        
    }
};
