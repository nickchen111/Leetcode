/*
503. Next Greater Element II
*/

// TC : O(2n) SC: O(n) 11/2
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        //變成考環形數組    
        stack<int> s;
        int n = nums.size();
        vector<int> res(n,-1);
        for(int i = 0; i<2*n; i++){
            while(!s.empty() && nums[s.top()%n] < nums[i%n]){
                res[s.top()%n] = nums[i%n];
                s.pop();
            }
            s.push(i);
        }

        return res;
    }
};

class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n);
        stack<int> s;

        //用加倍的方式來模擬環形數組 這樣在run第二輪的時候就會修改成環形數組的狀態
        for(int i = 2*n -1; i >= 0; i--){
            while(!s.empty() && nums[i%n] >= s.top()){
                s.pop();
            }

            ans[i%n] = s.empty() ? -1:s.top();
            s.push(nums[i%n]);
        }
        return ans;
    
    }
};

//tc : o(2n) sc: o(n)
