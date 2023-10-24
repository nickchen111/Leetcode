/*
153. Find Minimum in Rotated Sorted Array
*/

// 10/10 更簡單的思維 一步就判斷出 mid是在右還是左區間
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
            else {
                right = mid;//不斷往左邊限縮
            }
        }

        return nums[left];
    }
};

//"此題想求一個被rotate過的array 不曉得被轉過幾次 求他的最小值是多少 tc: o(lgn) sc: o(1)
class Solution {
public:
    int findMin(vector<int>& nums) {
        int left = 0;
        int right = nums.size()-1;
        while(left < right){
            int mid = left + (right - left)/2;

            if(nums[mid] >= nums[left]){//mid在左半區
                if(nums[mid] > nums[right]){
                    left = mid+1;
                }
                else right = mid;
            }

            else if(nums[mid] < nums[left] && nums[mid] <= nums[right]){ //mid 在右半區
                right = mid;
            }

        }
        return nums[left];
    }
};

/*
解題思維
"此題想求一個被rotate過的array 不曉得被轉過幾次 求他的最小值是多少
我第一個想到的是用與題目 33 類似的two pointer分出我求出的mid 是大排序位置的還是小排序位置的
再依此慢慢劃分到只剩一個元素即為我的最小值

第二個方法可以用遞歸不斷去求分割出來的那一段的最小值 因為不管怎麼切都必有一列會是排序好的 
那列的時間複雜度為o(1) 所以整體時間還是可以在o(lgn)找到 可參考LeetCode 153. Find Minimum in Rotated Sorted Array - 花花酱刷题找工作EP38"
*/
