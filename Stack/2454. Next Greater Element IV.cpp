/*
2454. Next Greater Element IV
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    vector<int> secondGreaterElement(vector<int>& nums) {
        int n = nums.size();
        stack<int> stk1;
        stack<int> stk2;
        vector<int> res(n,-1);
        for(int i = 0; i<n; i++){
            while(!stk2.empty() && nums[stk2.top()] < nums[i]){
                res[stk2.top()] = nums[i];
                stk2.pop();
            }
            vector<int> temp;
            while(!stk1.empty() && nums[stk1.top()] < nums[i]){
                temp.push_back(stk1.top());
                stk1.pop();
            }
            reverse(temp.begin(),temp.end());
            for(int x:temp) stk2.push(x);
            stk1.push(i);
        }

        return res;
    }
};


/*
此題想問每個數字往後看第二比他大的位置
用兩個stack 一個一樣是單調遞減 一個紀錄看過一次比他大的 
*/
