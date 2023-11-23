/*
2537. Count the Number of Good Subarrays
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    long long countGood(vector<int>& nums, int k) {
        long long res = 0;
        unordered_map<int,int> map;
        long long count = 0;
        int j = 0;
        int n = nums.size();
        for(int i = 0; i<nums.size(); i++){
            while(j < nums.size() && count < k){
                map[nums[j]]+=1;
                if(map[nums[j]] > 1) count+=(map[nums[j]]-1);
                j++;
            }
            if(count >= k){
                res+=(n-j+1);
            }
            if(map[nums[i]] > 1) count-=(map[nums[i]]-1);
            map[nums[i]]-=1;
        }
        return res;
    }
};

/*
此題限制
1.相同數字為一對pair 必須相等 
2.每個區間中pair數目大於等於k
[2,1,3,1,2,2,3,3,2,2,1,1,1,3,1]
                     j= 10
                     15-10+1 = 6 -> 5
count = 10 - > 12 j =11 -> 10
                     
*/
