/*
1589. Maximum Sum Obtained of Any Permutation
*/


// TC:O(n) SC:O(n)
class Solution {
    using LL = long long;
    LL M = 1e9+7;
public:
    int maxSumRangeQuery(vector<int>& nums, vector<vector<int>>& requests) {
        int n = nums.size();
        vector<int> diff(n+1,0);
        
        for(auto request : requests){
            diff[request[0]] += 1;
            diff[request[1]+1] -= 1;
        }

        vector<int> count;
        LL res = 0;
        LL sum = 0;
        for(int i = 0; i < nums.size(); i++){
            sum += diff[i];
            if(sum > 0){
                count.push_back(sum);
            }
        }

        sort(nums.rbegin(), nums.rend());
        sort(count.rbegin(), count.rend());
        for(int i = 0; i < count.size(); i++){
            res = (res + (count[i]*(LL)nums[i])) % M;
        }
        return res;
    }
};

/*
此題問你說一個數組你可以任意排序 然後給你一堆request區間
問說這些request區間總和在家總可以達到最大的總和為多少
任意排序只能排定成一種情況 剩下的request都要按照他的排序去做
我的想法是貪心的先去想區間重疊區域最多的地方給他排定最大的數字
x x x 
    x x x 
      x x x 
*/
