// TC:O(nlgn) SC:O(1)
class Solution {
    using LL = long long;
public:
    long long minCost(vector<int>& arr, vector<int>& brr, long long k) {
        LL cand1 = 0;
        int n = arr.size();
        for(int i = 0; i < n; i++) {
            cand1 = cand1 + abs(arr[i] - brr[i]);
        }
        LL cand2 = k;
        sort(arr.begin(), arr.end());
        sort(brr.begin(), brr.end());
        for(int i = 0; i < n; i++) {
            cand2 = cand2 + abs(arr[i] - brr[i]);
        }
        
        return min(cand1, cand2);
    }
};

/*
可以將數組重組 互相去找對於每個位置來說abs最小的數字 加總就會是答案
*/
