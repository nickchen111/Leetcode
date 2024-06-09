/*
3179. Find the N-th Value After K Seconds
*/

// TC:O(n*k) SC:O(n)
class Solution {
    using LL = long long;
    LL M = 1e9+7;
public:
    int valueAfterKSeconds(int n, int k) {
        vector<LL> arr(n,1);
        for(int i = 1; i <= k; i++){
            for(int j = 1; j < n; j++){
                arr[j] = (arr[j] + arr[j-1]) % M;
            }
        }
        
        return arr[n-1];
    }
};
