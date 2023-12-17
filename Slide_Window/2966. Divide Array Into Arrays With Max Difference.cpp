/*
2966. Divide Array Into Arrays With Max Difference
*/

// TC:O(nlgn + n ) SC:O(1)
class Solution {
public:
    vector<vector<int>> divideArray(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> res;
        int n = nums.size();
        int count = 0; 
        int minVal = -1;
        for(int i = 0; i < n; i++){
           if(count == 0){
               count+=1;
               minVal = nums[i];
           }
           else if(count && nums[i] - minVal <= k) {
               count++;
               if(count == 3){
                   res.push_back({nums[i-2],nums[i-1],nums[i]});
                   count = 0;
                }
           }
           else return {};
        }
       
       
       return res;
    }
};

/*
1. 分割數組到變成 長度3大小
2. 每個字都一定要使用＝＝ 週賽時WA兩次
3. 每個數組最大最小值差要小於等於k 
如果沒有這種分法返回空 有的話返回組合
先sort 就不用考慮-k的情況 
每次都去看當前數字跟當下數組的最小值相差是否<= k 是的話加入並且數組長度++ 
當長度達到目標就加入結果 並把計數器變回0
*/
