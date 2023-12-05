/*
2216. Minimum Deletions to Make Array Beautiful
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int minDeletion(vector<int>& nums) {
        int count = 0;//既是答案也是之後idx往前移的數量
        stack<int> stack;
        int n = nums.size();
        for(int i = 0; i < n; i++){
            if(!stack.empty() && (i-count) % 2 == 1 && nums[i] == stack.top()){
                stack.pop();
                count++;
            }
            stack.push(nums[i]);
        }

        if(stack.size() % 2 != 0) count++;
        return count; 
    }
};


// HG TC:O(n) SC:O(1)
class Solution {
public:
    int minDeletion(vector<int>& nums) {
        int n  = nums.size();
        int i = 0;
        int res = 0;
        while(i < n){
            int j = i + 1;
            while(j < n && nums[i] == nums[j]){
                j++;
                res++;
            }
            if(j < n){
                i = j+1;
            }
            else {
                res++;
                break;
            }
        }

        return res;
    }
};
/*
此題限制
nums.length is even. 
nums[i] != nums[i + 1] for all i % 2 == 0. 所有偶數idx 
if( (i-count) % 2 == 1 && nums[i] == stack.top()){
    res++;
    stack.pop();
}
最後檢查長度 如果不是奇數 任意刪除一個數
*/
