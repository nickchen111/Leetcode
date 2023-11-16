/*
718. Maximum Length of Repeated Subarray
*/

// TC:O(n^2) SC:O(n^2)
class Solution {
public:
    int findLength(vector<int>& nums1, vector<int>& nums2) {
        //我先把某個數組的可能性用hash set記起來 之後遍歷某個數組去找看看有沒有相同的
        int m = nums1.size(); int n = nums2.size();
        vector<vector<int>> dp(m+1,vector<int>(n+1,0));
        nums1.insert(nums1.begin(),0);
        nums2.insert(nums2.begin(),0);

        int res = 0;
        for(int i = 1; i<=m; i++){
            for(int j =1; j<=n; j++){
                if(nums1[i]==nums2[j]){
                    dp[i][j] = dp[i-1][j-1]+1;
                    res = max(res, dp[i][j]);
                }
                else dp[i][j] =0;
            }
        }

        return res;

    }
};

/*
longest common subarray 
dp[i][j]: the longest common subarray  that end at A[i] and B[j]
dp[i][j] = dp[i-1][j-1]+1 if A[i] == B[j] else 0

之前subsequence
dp[i][j] = d[i-1][j-1]+1 else max(dp[i][j-1],dp[i-1][j])
*/
