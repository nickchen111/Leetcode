/*
2780. Minimum Index of a Valid Split
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int minimumIndex(vector<int>& nums) {
        unordered_map<int, int> right, left;
        for(int i = 0; i < nums.size(); i++){
            right[nums[i]] += 1;
        }
        int n = nums.size();
        for(int i = 0; i < nums.size(); i++){
            left[nums[i]] += 1;
            right[nums[i]] -= 1;

            if((left[nums[i]] * 2 > i+1 ) && (right[nums[i]] * 2 > n-i-1)) return i;
        }
        
        return -1;
    }
};

/*
此題問符合dominant的最小idx在哪
dominant 要是出現頻率的元素*2 > subarray length
這樣想的話人人都有機會dominant 想法就變成先將所有數字頻率算出 
在用一個迴圈從頭紀錄 另一編就開始縮減 
如果符合了兩邊的條件那他就是最小idx
*/
