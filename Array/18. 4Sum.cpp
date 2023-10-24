/*
18. 4Sum
*/


// hash map TC:O(nlgn + n^3) SC:O(n)
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        unordered_map<long long,int> map;
        vector<vector<int>> res;
        for(int i = 0; i<n; i++){
            map[nums[i]]+=1;
        }

        for(int i = 0; i<n; i++){
            if(i && nums[i] == nums[i-1]) continue;
            for(int j = i+1; j<n; j++){
                if(j-1 != i && nums[j] == nums[j-1]) continue;
                for(int k = j+1; k<n; k++){
                    if(k-1 != j && nums[k] == nums[k-1]) continue;
                    long long sum = (long long)target - (long long)nums[i] - (long long)nums[j] - (long long)nums[k];
                    if(sum < nums[k]) continue;
                    if(!map.count(sum)) continue;
                    if(map[sum] >= 1 + (nums[i] == sum) + (nums[j] == sum) + (nums[k] == sum)){
                        res.push_back({(int)nums[i],(int)nums[j],(int)nums[k],(int)sum});
                    }
                }
            }
        }
        return res;
    }
};

// two pointer TC:O(nlgn + n^3) SC:O(1) 要加long long 才不會overflow
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        vector<vector<int>> res;
        for(int i = 0; i<n; i++){
            if(i && nums[i] == nums[i-1]) continue;
            for(int j = i+1; j<n; j++){
                if(j-1 != i && nums[j] == nums[j-1]) continue;
                int left = j+1; int right = n-1;
                while(left < right){
                    long long sum = (long long)nums[i] + (long long)nums[j] + (long long)nums[left] + (long long)nums[right];
                    if(sum > target){
                        right--;
                    }
                    else if(sum < target){
                        left++;
                    }
                    else{
                        res.push_back({nums[i],nums[j],nums[left],nums[right]});
                        while(left < right && nums[right] == nums[right-1]) right--;
                        while(left < right && nums[left] == nums[left+1]) left++;
                        left++;right--;
                    }
                }
            }
        }
        return res;
    }
};
