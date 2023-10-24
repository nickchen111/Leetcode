/*
33. Search in Rotated Sorted Array
*/

//二分搜尋法 tc: o(lgn) sc:o(1)
class Solution {
public:
    int search(vector<int>& nums, int target) {
        if(nums.size() == 0) return -1;
        int left = 0;
        int right = nums.size()-1;//必須減一 裡面會馬上用到nums[right]
        while(left < right){
            int mid = left+ (right-left)/2;
            if(target == nums[mid]) return mid;//跳出迴圈方式
            if(nums[left] <= nums[mid]){//mid在左邊這區
                if(target < nums[mid] && target >= nums[left]){
                    right = mid-1;
                }
                else left = mid+1;
            }
            else if(nums[left] > nums[mid]){ //mid 在右邊那區
                if(nums[mid] < target && nums[right] >= target){
                    left =mid+1;
                }
                else right = mid-1;
            }
        }
        //邊界條件判斷
        return nums[left] == target ? left:-1;
    }
};

// 10/7 TC:100%
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size()-1;
        //整體思路都是跟nums[0]在比
        while(left < right){
            int mid = left + (right- left)/2;
            if(target == nums[mid]) return mid;
            //如果mid 跟target同在左側
            if(nums[mid] >= nums[0] == target >= nums[0]){
                //按照原本套路去做
                if(nums[mid] < target){
                    left = mid+1;
                }
                else{
                    right = mid-1;
                }
            }
            //target在左區間
            else if(target >= nums[0]){
                right = mid-1;
            }
            //target 在右區間
            else left = mid+1;
        }

        if(left == right && nums[left] == target) return left;
        else return -1;
    }
};

/*
解題思維
1.先把中間點找到
2.寫條件判斷此中間點跟左右的關係 因為mid 可能會在前半區或後半區 
3.慢慢收斂直到找到target or target 不存在
注意while loop 條件left < right 的話裡面的程式碼 一定要讓left 有機會增加 或者是right要減少
*/
