/*
3250. Find the Count of Monotonic Pairs I
*/

// 次佳解 TC:O(n*m^2) SC:O(m*n)
class Solution {
    using LL = long long;
    LL M = 1e9+7;
public:
    int countOfPairs(vector<int>& nums) {
        int n = nums.size();
        vector<vector<LL>> dp(n+1, vector<LL>(51));
        nums.insert(nums.begin(), -1);
        for(int i = 0; i <= nums[1]; i++){
            dp[1][i] = 1;
        }
        
        for(int i = 2; i <= n; i++){
            int cur = nums[i];
            for(int j = 0; j <= min(cur, nums[i-1]); j++){
                int nums2_limit = nums[i-1] - j;
                if(dp[i-1][j]){
                    // j 是之前較小的limit, nums2_limit是up數組較大的
                    for(int k = cur; k >= j; k--){
                        if(nums2_limit >= cur-k){
                            dp[i][k] = (dp[i][k] + dp[i-1][j]) % M;
                        }
                        else break;
                    }
                }
            }
        }
        
        int res = 0;
        for(int i = 0; i <= 50; i++){
            res = (res + dp[n][i]) % M;
        }
        
        return res;
    }
};

/*
要讓兩個數組 一個非嚴格單調遞增 一個遞減
並且兩者相加等於原來數組 問說有幾對這種數組
dp[i][前面是多少數字] 走到i的時候有幾對這種數組
ex : i = 5, 0+5, 1+4, 2+3, 3+2, 4+1,5+0....
dp[i-1][1]

2 3 2 
0 : 2
1 : 1
2 : 0

0 -> 0 : 3
1 -> 1 : 2
2 -> 2 : 1
*/
