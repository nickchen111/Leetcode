/*
852. Peak Index in a Mountain Array
*/

//跟162題很像 找最高峰的題目 TC:O(lgn) SC:O(1)
class Solution {
public:
    int peakIndexInMountainArray(vector<int>& arr) {
        //找峰值的題目
        int left = 1;
        int right = arr.size()-2;
        while(left < right){
            int mid = left + (right -left)/2;
            if(arr[mid] < arr[mid+1]){
                left = mid+1;
            }
            else {
                right = mid;
            }
        }
        return left;
    }
};
