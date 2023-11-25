/*
2025. Maximum Number of Ways to Partition an Array
*/


// TC:O(n) SC:O(n)
class Solution {
public:
    int waysToPartition(vector<int>& nums, int k) {
        // 需 three pass
        int n = nums.size();
        long long total = accumulate(nums.begin(),nums.end(),0LL);//呼叫函式時還是需要特別注意給他LL型態
        vector<long long> presum(n);
        presum[0] = nums[0];
        for(int i = 1; i<n; i++){
            presum[i] = presum[i-1]+nums[i];
        }
        vector<long long> suf(n);
        suf[n-1] = nums[n-1];
        for(int i = n-2; i>=0; i--){
            suf[i] = suf[i+1]+nums[i];
        }

        vector<int> res(n);
        unordered_map<long long,int> map; // presum val->freq
        //將每個字輪流替換成k 看前面是否有符合的
        for(int i = 0; i<n; i++){
            long long new_sum = total-nums[i]+k;
            if(new_sum%2 == 0){
                res[i]+=map[new_sum/2];
            }
            map[presum[i]]+=1;
        }

        map.clear();
        //判斷後綴上有沒有
        for(int i = n-1; i>=0; i--){
            long long new_sum = total-nums[i]+k;
            if(new_sum%2 ==0){
                res[i]+=map[new_sum/2];
            }
            map[suf[i]]+=1;
        }
        //判斷原本的條件上有多少種
        int res0 = 0;
        //切分點不可以是最後一個
        for(int i=0; i<n-1; i++){
            if(total%2 ==0 && presum[i] == total/2){
                res0++;
            }
        }

        int ans = *max_element(res.begin(),res.end());
        ans = max(ans,res0);

        return ans;
    }
};
