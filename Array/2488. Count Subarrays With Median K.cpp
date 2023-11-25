/*
2488. Count Subarrays With Median K
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int countSubarrays(vector<int>& nums, int k) {
       
        int n = nums.size();
        for(auto &x:nums){
            if(x > k) x =1;
            else if(x < k) x = -1;
            else x=0;
        }

        int res = 0;
        unordered_map<int,int> presum_even;
        unordered_map<int,int> presum_odd;
        presum_even[0] = 1;//長度為偶數 前綴和為0的認為他存在 即subarray包含整個前綴
        // [xx x x x i]
        //  0.       
        
        int s = 0;
        // presum_even: how many prefixes whose sum equal s && length is even
        // presum_odd: how many prefixes whose sum equal s && length is odd
        for(int i = 0; i<n; i++){
            s+=nums[i];
            //奇數狀況
            if(i%2 == 0){
                res+=presum_even[s-0];
                res+=presum_odd[s-1];
                presum_odd[s]+=1;
            }
            //偶數狀況
            else {
                res+=presum_odd[s-0];
                res+=presum_even[s-1];
                presum_even[s]+=1;
            }
        }

        return res;
    }
};

/*
此題想求有多少個區間k這個數字會是區間的中位數
此題說每個數字都是獨特的所以不會重複
數字從1~n
k。一個數字要怎麼樣的性值排序才會是中位數
大於k的跟小於k的數字數量要相等 或者 大於k的多一個
轉化成三元數組 -> [-1 0 1] 相加為0 or 1
even_length sum = 1 符合
odd_length sum = 0符合

if([0:i] lenght is odd)
    res+=presum_even(s-0)
    res+=presum_odd(s-1)
if([0:i] lenght is even)
    res+=presum_even(s-1)
    res+=presum_odd(s-0)
*/
