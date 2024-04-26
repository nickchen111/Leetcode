/*
1673. Find the Most Competitive Subsequence
*/

// 4/26 更簡潔寫法 
class Solution {
public:
    vector<int> mostCompetitive(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> stack;
        int count = n-k;
        for(int i = 0; i < n; i++){
            // x x x x x 
            while(!stack.empty() && stack.back() > nums[i] && count > 0){
                count -= 1;
                stack.pop_back();
            }
            stack.push_back(nums[i]);
        } 

        while(stack.size() > k) stack.pop_back();


        return stack;
    }
};

// 限定刪除元素個數思維 TC:O(n) SC:O(n)
class Solution {
public:
    vector<int> mostCompetitive(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> stack;
        int count = n-k;
        for(int i = 0; i < n; i++){
            if(stack.empty() || stack.back() <= nums[i]){
                stack.push_back(nums[i]);
            }
            else {
                while(!stack.empty() && count > 0 && stack.back() > nums[i]){
                    stack.pop_back();
                    count--;
                }
                stack.push_back(nums[i]);
            }
        }

        while(count){
            stack.pop_back();
            count--;
        }

        return stack;
    }
};

// 另一種思維: 限定最後數組長度思維 TC:O(n) SC:O(n)
class Solution {
public:
    vector<int> mostCompetitive(vector<int>& nums, int k) {
        vector<int> res;
        int n = nums.size();
        vector<int> stack;
        
        for(int i = 0; i < n; i++){
            while(!stack.empty() && stack.back() > nums[i] && stack.size() + n-i > k){
                stack.pop_back();
            }
            stack.push_back(nums[i]);
            if(stack.size() == k) res = stack;
        }
        
        if(res.size() < k) {
            res.clear();
            for(int i = n-k; i < n; i++){
                res.push_back(nums[i]);
            }
            return res;
        }
        else {
            return res;
        }
    }
};



/*
此題要在一個數組內找出 k長度的遞增數列並且 它具有競爭力的條件是他的位子上的數字會比跟他相等長度的數列中數字來的一樣或者小
Stack做 要保持k個大小意味著只能刪除n-k個 or 去想說最後數組尾巴如果stack裡面的元素+(n-i)個 小於等於k那就不能再刪了
9 8 7 6 5 4 3 2 1 , k = 2
*/
