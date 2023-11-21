/*
2009. Minimum Number of Operations to Make Array Continuous
*/

// TC:O(nlgn+n) SC:O(n)
class Solution {
public:
    int minOperations(vector<int>& nums) {
        // slide window
        int n = nums.size();//原始大小n
        unordered_set<int> set(nums.begin(),nums.end());//去重
        vector<int> arr(set.begin(),set.end());
        sort(arr.begin(),arr.end());
        int res = INT_MAX;
        int j = 0;
        for(int i = 0; i<arr.size(); i++){
            //算出這個跨度如果當作起始點的話會需要的元素長度 如果在n以內代表可行
            while(j < arr.size() && arr[j]-arr[i]+1 <= n){
                int need = n-(j-i+1);
                res = min(res,need);
                j++;
            }
        }

        return res;
    }
};
