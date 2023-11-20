/*
974. Subarray Sums Divisible by K
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int subarraysDivByK(vector<int>& nums, int k) {
        unordered_map<int,int> map; // prefix%k-> val
        map[0] = 1;
        int presum = 0;
        int res = 0;
        for(int i= 0; i<nums.size(); i++){
            presum+=nums[i];
            int r = (presum%k+k)%k; //怕是負數 要轉成正
            if(map.find(r) != map.end()){
                res+=map[r];
            }
            map[r]+=1;
        }

        return res;
    }
};

/*
(presum[i]-presum[j-1])/k = 整數
如果兩個數被k除餘數相等那麼相減就可以被k除==
*/
