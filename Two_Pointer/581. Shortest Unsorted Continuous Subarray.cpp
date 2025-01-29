// Two Pointer TC:O(n) SC:O(1)
class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        int n = nums.size();
        int left = 0, right = n - 1;
        while(left < n-1 && nums[left] <= nums[left+1]) left += 1;
        if(left == n - 1) return 0;
        while(right > 0 && nums[right] >= nums[right-1]) right -= 1;
        int mx = INT_MIN, mn = INT_MAX;
        for(int i = left; i <= right; i++) {
            mx = max(mx, nums[i]);
            mn = min(mn, nums[i]);
        } 
        while(left-1 >= 0 && nums[left-1] > mn) left -= 1;
        while(right < n-1 && nums[right+1] < mx) right += 1;
        return right - left + 1;
    }
};

// Stack TC:O(n) SC:O(n)
class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        int n = nums.size();
        // stack
        vector<int> prevGreater(n,-1);
        stack<int> stack;
        for(int i = 0; i < n; i++) {
            while(!stack.empty() && nums[stack.top()] <= nums[i]) stack.pop();
            if(!stack.empty()) prevGreater[i] = stack.top();
            stack.push(i);
        }
        while(!stack.empty()) stack.pop();
        vector<int> nxtSmaller(n,n);
        for(int i = n - 1; i >= 0; i--) {
            while(!stack.empty() && nums[stack.top()] >= nums[i]) stack.pop();
            if(!stack.empty()) nxtSmaller[i] = stack.top();
            stack.push(i);
        }
        int left = INT_MAX, right = INT_MIN;
        for(int i = n - 1; i >= 0; i--) {
            if(prevGreater[i] != -1) {
                right = max(right, i);
                left = min(prevGreater[i], left);
            }
            if(nxtSmaller[i] != n) {
                left = min(left, i);
                right = max(right, nxtSmaller[i]);
            }
        }
        return left == INT_MAX ? 0 : right - left + 1;
    }
};

// Sort
class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        int n = nums.size();
        vector<int> arr = nums;
        ranges::sort(arr);
        if(arr == nums) return 0;
        int left = -1, right = -1;
        for(int i = 0; i < n; i++) {
            if(arr[i] != nums[i]) {
                if(left == -1) {
                    left = i;
                    right = i;
                }
                else right = i;
            }
        }
        return right - left + 1;
    }
};
