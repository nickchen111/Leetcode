/*
26. Remove Duplicates from Sorted Array
*/

// bst Method

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        if(n == 0) return 0;
        int res = 1;
        for(int i = 1; i < n; i++) {
            if(nums[i] != nums[i-1]) {
                nums[res] = nums[i];
                res += 1;
            }
        }
        return res;
    }
};

//TC:O(n) SC:O(1)
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int slow = 0; int fast = 1;
        while(fast < nums.size()){
            if(nums[slow] != nums[fast]){
                slow++;
                nums[slow] = nums[fast];
            }
            fast++;
        }

        return slow+1;
    }
};
