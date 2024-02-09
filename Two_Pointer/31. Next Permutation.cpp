/*
31. Next Permutation
*/

// TC:O(nlgn) SC:O(1)
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        //後面的數字往後看 看有沒有比他大的數字 如果有就換位置 然後換過去的數字再從那裡出發往後換
        int n = nums.size();
        
        int i=n-1;
        while(i-1>=0 && nums[i-1] >=nums[i]){
            i--;
        }
        if(i == 0) {
            sort(nums.begin(),nums.end());
            return;
        }

        i--;//才會是要替換的位置
        int j = n-1;//找要跟誰換
        while(nums[j] <= nums[i]) j--;
        swap(nums[i],nums[j]);

        sort(nums.begin()+i+1,nums.end());
        return;
    }
};

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();
        std::stack<int> stack;
        int idx = -1;
        for(int i = n-1; i >= 0; i--){
            //兩個交換 後面的元素直接sort
            //維護一個單調遞增序列
            while(!stack.empty() && nums[stack.top()] > nums[i]){
                idx = stack.top();
                stack.pop();
            }
            if(idx != -1){
                swap(nums[i], nums[idx]);
                // x x x i x x x idx
                sort(nums.begin()+i+1,nums.end());
                break;
            }
            stack.push(i);
        }
        if(idx == -1){
            sort(nums.begin(), nums.end());
        }
    }
};

/*
求下一個排列組合的狀況
2 3 3 ->  
n = 100

此題要從思維上想通再去寫代碼 看出題目的邏輯 一定是從後面開始往前看 看能否找到一位前面比後面小的 在找出要跟他換的那個稍微大一點的數字
最後去做排序即可
*/
