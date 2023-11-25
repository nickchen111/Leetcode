/*
2588. Count the Number of Beautiful Subarrays
*/

// TC:O(32*n) SC:O(n)
class Solution {
public:
    long long beautifulSubarrays(vector<int>& nums) {
        long long res = 0;
        int n = nums.size();
        long long state = 0;
        unordered_map<long long,int> map;
        map[0] = 1;
        for(int i=0; i<n; i++){
            int b = nums[i];
            for(int k = 0; k<32; k++){
                int t = (((state>>k)&1) + ((b>>k)&1))%2;
                //先把原本的扣掉再加上新的
                state = state - (((state>>k)&1)<<k) + (t<<k);
            }
            res+=map[state];
            map[state]+=1;
        }

        return res;
    }
};

/*
此題考每個區間的bit為總和都必須是偶數 才能藉由題目內的操作消成0
同樣也就是考察奇偶數同質考題
*/
