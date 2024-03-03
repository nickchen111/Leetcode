/*
3069. Distribute Elements Into Two Arrays I
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    vector<int> resultArray(vector<int>& nums) {
        int n = nums.size();
        vector<int> arr1;
        vector<int> arr2;
        
        for(int i = 0; i < n; i++){
            if(i == 0){
                arr1.push_back(nums[i]);
            }
            else if(i == 1){
                arr2.push_back(nums[i]);
            }
            else {
                if(arr1.back() > arr2.back()){
                    arr1.push_back(nums[i]);
                }
                else if(arr2.back() > arr1.back()){
                    arr2.push_back(nums[i]);
                }
            }
        }
        
        vector<int> res;
        for(auto x : arr1){
            res.push_back(x);
        }
        for(auto x : arr2){
            res.push_back(x);
        }
        
        return res;
    }
};
