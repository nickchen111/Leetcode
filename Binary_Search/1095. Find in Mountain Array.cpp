/*
1095. Find in Mountain Array
*/

// TC:O(lgn + lga + lgb) SC:O(1)
class Solution {
public:
    int findInMountainArray(int target, MountainArray &mountainArr) {
        int n = mountainArr.length();
        
        int maxPos = -1;
        int left = 0, right = n-1;
        while(left < right){
            int mid = left + (right-left)/2;
            int maxVal = mountainArr.get(mid);
            int leftVal = mountainArr.get(mid-1);
            int rightVal = mountainArr.get(mid+1);
            if(maxVal > leftVal && maxVal > rightVal){
                maxPos = mid;
                break;
            }
            else if(maxVal > leftVal && maxVal < rightVal){
                left = mid + 1;
            }
            else if(maxVal < leftVal && maxVal > rightVal){
                right = mid;
            }
        }
        
        int left1 = 0, right1 = maxPos;
        while(left1 < right1){
            int mid = left1 + (right1-left1)/2;
            if(mountainArr.get(mid) >= target){
                right1 = mid;
            }
            else left1 = mid+1;
        }
        if(mountainArr.get(left1) == target) return left1;

        int left2 = maxPos+1, right2 = n-1;
        while(left2 < right2){
            int mid = left2 + (right2-left2+1)/2;
            if(mountainArr.get(mid) >= target){
                left2 = mid;
            }
            else right2 = mid-1;
        }
        if(mountainArr.get(left2) == target) return left2;
        else return -1;
    }
};

/*
給你一個是山狀的數組 要你找某個target是否在這個數組內 如果有返回最小的那個index沒有的話返回-1
如何對兩邊做Binary search? 先找出峰值的index 然後對他左右邊做二分 (兩邊都是有序的了 不過右邊那個是倒敘的) 
*/
