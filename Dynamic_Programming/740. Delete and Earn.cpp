/*
740. Delete and Earn
*/

// TC:O(nlgn + n) SC:O(n)
class Solution {
public:
    int deleteAndEarn(vector<int>& nums) {
        unordered_map<int,int> map;// 數字對應次數
        unordered_set<int> set(nums.begin(),nums.end());//去重
        vector<int> arr(set.begin(),set.end());//取出來
        sort(arr.begin(), arr.end());

        for(auto num:nums){
            map[num]+=1;
        }

        int n = arr.size();
        int take = arr[0]*map[arr[0]];
        int notake = 0;
 
        for(int i = 1; i < n; i++){
            auto take_tmp = take, notake_tmp = notake;
            if(arr[i] == arr[i-1]+1){
                take = notake_tmp+ map[arr[i]]*arr[i];
                notake = max(take_tmp, notake_tmp);
            }
            else {
                take = max(take_tmp, notake_tmp) + map[arr[i]]*arr[i];
                notake = max(notake_tmp, take_tmp);
            }
        }

        return max(take, notake);
    }
};
