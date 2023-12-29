/*
2871. Split Array Into Maximum Number of Subarrays
*/

// TC:O(n) SC:O(1)
class Solution {
public:
    int maxSubarrays(vector<int>& nums) {
        int n = nums.size();
        int minVal = nums[0];
        for(int i = 1; i < n; i++){
            minVal &= nums[i];
        }
        
        int res = 0;
        int i = 0;
        int sum = 0;
        while(i < n){
            int temp = nums[i];
            int j = i;
            while(j+1 < n && temp != minVal){
                j++;
                temp &= nums[j];
            }
            if(temp == minVal && sum == minVal){
                sum += temp;
                res += 1;
            }

            i = j+1;
        }

        return max(1,res);
    }
};


/*
想將array 切割成若干可以不切割 subarray 加總出的最小 能切割出最多幾個subarray
AND 是越多數字越小 先 AND一遍 然後遍歷數組 一但到達AND的答案 res++ 並且 加總答案 但如果沒辦法到達 直接返回1
*/
