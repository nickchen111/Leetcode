/*
34. Find First and Last Position of Element in Sorted Array

*/

// TC:O(lgn) SC:O(1)
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> res;
        //先找左邊的是否存在
        int n = nums.size();
        int left = 0;
        int right = n-1;
        while(left < right){
            int mid = left+(right-left)/2;
            if(nums[mid] == target){
                right = mid;
            }
            else if(nums[mid] < target){
                left = mid+1;
            }
            else right = mid-1;
        }

        if(left == right && nums[left] == target){
            res.push_back(left);
        }
        else res.push_back(-1);

        left = 0; right = n-1;
        //開始找右邊的
        while(left < right){
            int mid = left+(right-left+1)/2;
            if(nums[mid] == target){
                left = mid;
            }
            else if(nums[mid] < target){
                left = mid+1;
            }
            else right = mid-1;
        }

        if(left == right && nums[left] == target){
            res.push_back(left);
        }
        else res.push_back(-1);

        return res;

    }
};

//善用c++ API lowerbound upperbound：（這兩個的時間複雜度為lgn) TC:O(lgn) SC:O(1)
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> ans;
        auto pos = lower_bound(nums.begin(), nums.end(), target);//去找大於或等於target的那個位置
        if(pos != nums.end() && *pos == target){
            ans.push_back(pos - nums.begin()); //相減可求出index
        }
        else ans.push_back(-1);

        pos = upper_bound(nums.begin(), nums.end(), target); //去找大於的那個位置
        pos = prev(pos, 1);
        if(pos != nums.begin() && *pos == target){
            ans.push_back(pos -nums.begin());
        }
        else ans.push_back(-1);

        for(auto x:ans){
            cout << x<< endl;
        }

        return ans;
    }
};

//labuladong  TC:O(lgn) SC:O(1)
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int left = leftbound(nums, target);
        int right = rightbound(nums, target);
        return {left, right};
    }
    int leftbound(vector<int>& nums, int target){//找左側邊界
        int left = 0;
        int right = nums.size(); //左閉右開

        while(left < right){ //出去條件left = right
            int mid = left + (right - left) /2;
            if(nums[mid] == target){ 
                right = mid;
            }
            else if(nums[mid] < target){
                left = mid + 1;//左閉
            }
            else if(nums[mid] > target){
                right = mid; //右開
            }
        }
        //確認邊界
        if(left < 0 || left >= nums.size()) return -1;

        return nums[left] == target ? left:-1;
    }
    int rightbound(vector<int>& nums, int target){//找右側邊界
        int left = 0;
        int right = nums.size(); //左閉右開

        while(left < right){ //出去條件left = right
            int mid = left + (right - left)/2;

            if(nums[mid] == target) left = mid+1; //左閉
            else if(nums[mid] > target){
                right = mid;
            }
            else if(nums[mid] < target){
                left = mid+1;
            }
        }

        //判斷邊界條件
        if( left -1 < 0 || left-1 >= nums.size()) return -1;// left-1的原因是走到nums[mid] == target 時left mid會被加一

        return nums[left-1] == target ? left-1:-1;
    }

};

/*
解題思路
分成查找左側邊界跟右側邊界
*/
