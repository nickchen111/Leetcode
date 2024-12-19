/*
2593. Find Score of an Array After Marking All Elements
*/

// TC:O(n) SC:O(n) 也可以用PQ解
class Solution {
    using LL = long long;
public:
    long long findScore(vector<int>& nums) {
        nums.push_back(INT_MAX);
        int n = nums.size();
        stack<int> stack;
        LL res = 0;
        for(int i = 0; i < n; i++) {
            if(stack.empty() || stack.top() > nums[i]) {
                stack.push(nums[i]);
            }
            else {
                while(!stack.empty()) {
                    res += stack.top();
                    stack.pop();
                    if(!stack.empty()) stack.pop();
                }
            }
        }
        

        return res;
    }
};
