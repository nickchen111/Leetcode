/*
3177. Find the Maximum Length of a Good Subsequence II
*/

//  TC:O(k*n) SC:O(k+n*k)
class Solution {
public:
    int maximumLength(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_map<int, vector<int>> map; // 5*1e3 * 50
        
        vector<int> arr(k+1,0);
        
        for(int i = 0; i < n; i++){
            if(map.find(nums[i]) == map.end()){
                map[nums[i]].resize(k+1,0);
            }

            for(int j = k; j >= 0; j--){
                map[nums[i]][j] += 1; // 先嘗試之前有出現過的狀況+1 就算沒有也就是變成0+1
                if(j > 0){
                    map[nums[i]][j] = max(map[nums[i]][j], arr[j-1] + 1);//不用去判斷j-1那項是否nums相等 因為就算相等 這裡也不會被更新
                }

                arr[j] = max(arr[j], map[nums[i]][j]);
            }
        }

        return arr.back();
    }
};
