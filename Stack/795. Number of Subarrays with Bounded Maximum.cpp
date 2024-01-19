/*
795. Number of Subarrays with Bounded Maximum
*/

// TC:O(n*3) SC:O(n)
class Solution {
public:
    int numSubarrayBoundedMax(vector<int>& nums, int left, int right) {
        int n = nums.size();
        vector<int> prevGreater(n,-1);
        vector<int> nextGreater(n,n);
        stack<int> stack; //約定俗成 往右看的話可以超過自己 往左不行        
        for(int i = 0; i < n; i++){
            while(!stack.empty() && nums[stack.top()] <= nums[i]){
                stack.pop();
            }
            if(!stack.empty()) prevGreater[i] = stack.top();
            stack.push(i);
        }
        while(!stack.empty()) stack.pop();
        for(int i = n-1; i >= 0; i--){
             while(!stack.empty() && nums[stack.top()] < nums[i]){
                stack.pop();
            }
            if(!stack.empty()) nextGreater[i] = stack.top();
            stack.push(i);
        }

        int res = 0;
        for(int i = 0; i < n; i++){
            if(nums[i] >= left && nums[i] <= right){
                int a = i - prevGreater[i];
                int b = nextGreater[i] - i;
                res += (a*b);
            }
        }

        return res;
    }
};

/*
將所有的subarray其最大元素介於 left~right之間的數字都計算出來
數subarray
1. hash + prefix sum 可能會用到二分或者直接map
2. 模擬每個點的狀況數subarray都去找他的特徵值 根據提議模擬 想說如果此點是最大值他可以涵蓋多少區間
*/
