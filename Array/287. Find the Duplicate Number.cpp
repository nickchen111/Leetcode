/*
287. Find the Duplicate Number
*/

// index sort TC:O(n) SC:O(1)
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        // index sort
        int n = nums.size();
        nums.insert(nums.begin(),0);
        for(int i = 1; i<=n;i++){
            while(nums[i] != i && nums[i] <=n && nums[i] != nums[nums[i]]){
                swap(nums[i],nums[nums[i]]);
            }
        }
        for(int i = 1; i<=n; i++){
            if(nums[i] != i) return nums[i];
        }

        return -1;
    }
};

//Binary search TC:O(nlgn) SC:O(1)
lass Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int left = 1;
        int right = nums.size()-1;
        //猜數字
        while(left < right){
            int k = left + (right-left)/2;
            int count = 0;
            for(int i = 0; i< nums.size(); i++){
                if(nums[i] <= k) count++;
            }
            //有可能是答案 但也可能找太大的數字了
            if(count > k) right = k;
            else left = k+1;
        }

        return left;
    }
};
/*
此題其實在neetcode被歸類為 linked list 用 detect cycle那招 想像 先從每個index->val 不斷循環最後如果有重複的就會有cycle 
*/
