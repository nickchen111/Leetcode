/*
162. Find Peak Element
*/


//看懂題目題是很重要 兩個端點為低谷 所以中間一定有peak
// 10/7 打卡 二分 TC:O(lgn) SC:O(1)
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int left = 0;
        int right = nums.size()-1;
        while(left < right){
            int mid = left + (right - left)/2;
            if(nums[mid] < nums[mid+1]){
                left = mid+1;
            }
            else{
                right = mid;
            }
        }
        return left;
    }
};


//binary search 
class Solution1 {
public:
    int findPeakElement(vector<int>& nums) {
        int high = nums.size()-1;
        int low = 0;
        int n = nums.size();
        while(low < high){//就是要找到等於的時候
            int mid = low + (high - low) /2;
            if(nums[mid] > nums[mid+1]){
                high = mid;
            }
            else low = mid+1;
        }
        return low;
    }
};

//BINARY SEARCH--> recursion方式 
// Time Complexity : O(log N), since we have used binary search to find the target element. The time complexity is logarithmic.
//Space Complexity : O(logN), Recursion stack space.
class Solution2 {
public:
    int findPeakElement(vector<int>& nums) {
        return recursion_binary_search(nums, 0, nums.size()-1 );
    }
private:
    int recursion_binary_search(vector<int> &nums, int low, int high){
        if(low == high) return low;
        while(low < high){
            int mid = low + (high -low)/2;
            if(nums[mid] > nums[mid+1]) return recursion_binary_search(nums, low, mid);
            else return recursion_binary_search(nums, mid+1, high);
        }
        return -1;
    }
};
//brute forc方式 time: o(n) space: o(1)
class Solution3 {
public:
    int findPeakElement(vector<int>& nums) {
        int n = nums.size();
        for(int i = 0; i < n-1; i++){
            if(nums[i] > nums[i+1]) return i;
        }
        return n-1;
    }
};

//我覺得可以接受的解釋
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int high = nums.size()-1; // 我们需要比较 nums[mid] 和 nums[mid+1] 的大小关系，因此 mid+1 不能越界，所以我们需要保证 mid 的取值范围在 [0, nums.size()-2] 内，否则 mid+1 就会越界。 
        int low = 0;
        while(low < high){//就是要找到等於的時候
            int mid = low + (high - low)/2;
            if(nums[mid] > nums[mid+1]){
                high = mid;//右開
            }
            else if(nums[mid] < nums[mid+1]) {
                low = mid+1;//左閉
            }

        }
        return low;
    }
};
