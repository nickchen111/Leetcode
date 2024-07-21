/*
2772. Apply Operations to Make All Array Elements Equal to Zero
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    bool checkArray(vector<int>& nums, int k) {
        int n = nums.size();
        if(k == 1) return true;
        vector<int> diff(n+k);
        int sum = 0;
        for(int i = 0; i < n; i++){
            sum += diff[i];
            int cur = nums[i] + sum;
            if(cur > 0){
                diff[i] -= (cur);
                sum -= cur;
                if(i+k > n) return false; // x x x x 
                diff[i+k] += (cur);
            }
            else if (cur < 0) return false;
        }

        return true;
    }
};

/*
想法會是 要是非遞減的長度為k的數列 才可以執行 並且要去判斷他會剩下多少數字 與後面的結合
[27,99,7,1,94,63,84,46,76,35,97,77,19,72,3]
k = 2
*/
