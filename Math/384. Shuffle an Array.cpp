/*
384. Shuffle an Array
*/

//TC:O(n) SC:O(n)
class Solution {
    int n;
    vector<int> nums;
public:
    Solution(vector<int>& nums) {
        this->nums = nums;
        n = nums.size();
    }
    
    vector<int> reset() {
        return nums;
    }
    
    vector<int> shuffle() {
        vector<int> clone = nums;
        for(int end = n-1; end>=0; end--){
            int r = rand()%(end+1);//選中目前範圍內允許的index
            swap(clone, r, end);//將他跟目前最後面的那個index交換  之後選中那個就再也選不到哩 因為範圍不斷縮小
        }

        return clone;
    }

    void swap(vector<int>& clone, int r, int end){
        auto temp = clone[r];
        clone[r] = clone[end];
        clone[end] = temp;
    }
};

/*
"洗牌問題 
沒辦法用srand() rand() 的方式通過此題 此題p value要求應該就是要 > 0.05那種的規格
必須用shuffle 演算法
證明他在隨機洗牌所有數字且不會重複的情況下會是每個數字相同機率:x
int i = 0; [0:n-1] 1/n
int i = 1; [1:n-1] (n-1)/n * (1/n-1) = 1/n 上次沒被選上的機率 乘上這次選上的機率"
*/
