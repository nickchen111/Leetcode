/*
154. Find Minimum in Rotated Sorted Array II
*/

class Solution {
public:
    int findMin(vector<int>& nums) {
        int left = 0;
        int right = nums.size()-1;

        while(left < right){
            int mid = left + (right - left)/2;

            //在左邊區間的狀況 想移到右區間
            if(nums[mid] > nums[right]){
                left = mid+1;
            }
            else if(nums[mid] < nums[right]){
                right = mid;//不斷往左邊限縮
            }
            else {
                right-=1;//把最尾巴重複的不考慮 如果最小就是最尾巴的樹也沒關係 會收斂到mid上
            }
        }
        return nums[left];
    }
};

/*
可能會有以下幾種情況
[2 2 2 2 3 4 0 1 2]
       M         R
[2 2 2 3 4 0 1 2 2 2 2 2 2 2 2 2 2 2]
                 M                 R
[2 2 2 2 2 2 2] 這個情況的話會變成O(n)
       M.    R
*/
