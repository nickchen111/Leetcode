/*
1191. K-Concatenation Maximum Sum
*/

// TC:O(n) SC:O(n)
class Solution {
    using LL = long long;
    int M = 1e9+7;
public:
    int kConcatenationMaxSum(vector<int>& arr, int k) {
        
        if(k == 1){
            return kadane(arr);
        }

        LL sum = 0;
        LL res = 0;
        for(int i = 0; i < arr.size(); i++){
            sum = (sum + arr[i]) % M;
        }

        
        //將他變兩倍
        vector<int> arr2(arr);
        arr2.insert(arr2.end(), arr.begin(), arr.end());
        if(k == 2) return kadane(arr2) % M;

        if(sum < 0){
            return kadane(arr2) % M;
        }

        else 
            return (kadane(arr2) + ((LL)(k-2)*sum) % M) % M;
    }

    LL kadane(vector<int>& arr){
        LL maxVal = 0;
        LL max_ending_here = 0;
        for(int i = 0; i < arr.size(); i++){
            max_ending_here = (max_ending_here +  arr[i]);
            if(max_ending_here < 0){
                max_ending_here = 0;
            }
            maxVal = max(maxVal, max_ending_here);
        }

        return maxVal;
    }
};

/*
給你一數組 要你重複他裡面的數值k次 問你此重複的數組中的子數組最大為多少
T > 0 A TTT. TTTTB T代表重複的整段數組 
T == 0 首尾AB兩段就好

Kadane 遍歷的時候紀錄最小值 與最大值 看他們之間的差
*/
