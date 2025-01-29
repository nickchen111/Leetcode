// 2 pointer TC:O(n) SC:O(1)
class Solution {
public:
    int maximumScore(vector<int>& nums, int k) {
        int n = nums.size();
        int ans = nums[k];
        int left = k-1, right = k+1;
        int mn = nums[k];
        while(left >= 0 || right < n) {
            // cout << left << ' ' << right << endl;
            if(right == n || (left >= 0 && nums[left] >= nums[right])) {
                mn = min(mn, nums[left--]);
            }
            else if(left == -1 || nums[left] < nums[right]){
                mn = min(mn, nums[right++]);
            }
            ans = max(ans, (right - left - 1) * mn);
        }
        return ans;
    }
};

/*
長度 * min(i ... j)
從k開始發散向兩端出發 每走一步就選擇當下較大的數字
*/

// Stack TC:O(n) SC:O(n)
class Solution {
public:
    int maximumScore(vector<int>& nums, int k) {
        int n = nums.size();
        stack<int> stack;
        vector<int> nxtSmaller(n,n);
        for(int i = n - 1; i >= 0; i--) {
            while(!stack.empty() && nums[stack.top()] >= nums[i]) stack.pop();
            if(!stack.empty()) nxtSmaller[i] = stack.top();
            stack.push(i);
        }
        while(!stack.empty()) stack.pop();
        int ans = nums[k];
        for(int i = 0; i < n; i++) {
            while(!stack.empty() && nums[stack.top()] >= nums[i]) stack.pop();
            int prev = -1;
            if(!stack.empty()) prev = stack.top();
            if(prev < k && nxtSmaller[i] > k) {
                ans = max(ans, nums[i] * (nxtSmaller[i] - prev - 1));
            }
            stack.push(i);
        }
        return ans;
    }
};
