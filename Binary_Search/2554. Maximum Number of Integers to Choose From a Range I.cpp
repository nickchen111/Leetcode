/*
2554. Maximum Number of Integers to Choose From a Range I
*/

// TC:O(mlgm + lgn * lgm) SC:O(m)
class Solution {
public:
    int maxCount(vector<int>& banned, int n, int maxSum) {
        // x x x x x x x 
        int total = n*(n+1)/2; // 他會有個總和
        int bsum = 0;
        set<int> set;
        for(int i = 0; i < banned.size(); i++) {
            if(banned[i] <= n && set.find(banned[i]) == set.end()) {
                bsum += banned[i];
                set.insert(banned[i]);
            }
        }
        
        if(total - bsum <= maxSum) return n - (int)set.size(); 
        
        vector<int> arr(set.begin(), set.end());

        int m = set.size();
        vector<int> presum(m+1);
        for(int i = 0; i < m; i++) {
            presum[i+1] = presum[i] + arr[i]; // 到某個數字為止的和
        }

        auto check = [&](int mid) {
            int total = mid*(mid+1)/2;
            auto iter = upper_bound(arr.begin(), arr.end(), mid);
            int idx = iter - arr.begin();
            return total - presum[idx] <= maxSum;
        };

        int left = 0, right = n;
        while(left < right) {
            int mid = left + (right-left+1)/2;
            if(check(mid)) {
                left = mid;
            }
            else right = mid - 1;
        }
        auto iter = upper_bound(arr.begin(), arr.end(), left);
        return left - (iter - arr.begin());
    }
};

/*
所選數字不能超過n
banned裡面數字不能選 
選一段數字 總和不能超過maxSum
現在 n很大 然後maxSum也很大 要怎麼求出有幾個數字可以選
*/
