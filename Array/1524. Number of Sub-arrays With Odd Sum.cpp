/*
1524. Number of Sub-arrays With Odd Sum
*/


// TC:O(n) SC:O(1)
class Solution {
    long long M = 1e9+7;
public:
    int numOfSubarrays(vector<int>& arr) {
        long oddCount = 0; long evenCount = 1;//因為沒東西的時候如果第一個數字是odd那麼在-1的位置上代表什麼都沒有0->even
        long res = 0;
        long presum = 0;
        for(int i = 0; i<arr.size(); i++){
            presum+=arr[i];
            if(presum%2 == 1){
                res+=evenCount;
                oddCount++;
            }
            else{
                res+=oddCount;
                evenCount++;
            }
            res%=M;
        }

        return res;
    }
};
