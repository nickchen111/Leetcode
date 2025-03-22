/*
1959. Minimum Total Space Wasted With K Resizing Operations
*/

// 2025.03.22 優化遞推 TC:O(n * k * n) SC:O(n * k)
class Solution {
public:
    int minSpaceWastedKResizing(vector<int>& nums, int k) {
        int n = nums.size();
        int f[n+1][k+1];
        for (int i = 0; i <= n; i++)
            fill(f[i], f[i] + k + 1, INT_MAX/2);
        f[0][0] = 0;
        int mx = 0, tot = 0;
        for (int i = 0; i < n; i++) {
            mx = max(mx, nums[i]);
            tot += nums[i];
            f[i + 1][0] = mx * (i + 1) - tot;
        }
        
        for (int i = 0; i < n; i++) {
            int groups = min(i + 1, k);
            // j 表示已完成的切分數（0-indexed，j+1 段）
            for (int j = 0; j < groups; j++) {
                mx = 0, tot = 0;
                for (int t = i; t >= 0; t--) {
                    // 如果 t < j，表示前 t 個元素不足以分成 j+1 段，提前結束
                    if (t + 1 < j) break;
                    mx = max(mx, nums[t]);
                    tot += nums[t];
                    f[i + 1][j + 1] = min(f[i + 1][j + 1], f[t][j] + mx * (i - t + 1) - tot);
                }
            }
        }
        return f[n][k];
    }
};



// TC:O(n*k*n) SC:O(n*k)
class Solution {
public:
    int minSpaceWastedKResizing(vector<int>& nums, int k) {
        int n = nums.size();
        int dp[n][k+1];
        for(int i = 0; i < n; i++){
            for(int j = 0; j <= k; j++){
                dp[i][j] = INT_MAX/2;
            }
        }
        //初值設定 都沒做操作的代價
        int mx = 0;
        int sum = 0;
        for(int i = 0; i < n; i++){
            mx = max(mx, nums[i]);
            sum += nums[i];
            dp[i][0] = mx*(i+1) - sum;
        }

        for(int i = 1; i < n; i++){
            for(int j = 1; j <= min(i,k); j++){
                int mx = 0;
                int intervalSum = 0;
                //反著走才不用每次都重新走一遍
                for(int s = i; s >= 1; s--){
                    mx = max(mx, nums[s]);
                    intervalSum += nums[s];
                    dp[i][j] = min(dp[i][j], dp[s-1][j-1] + mx*(i-s+1) - intervalSum);
                }
            }
        }

        int res = INT_MAX/2;
        for(int j = 0; j <= k; j++){
            res = min(res, dp[n-1][j]);
        }

        return res;
    }
};

/*
此題與1043 1105相似
此題問說如果你可以走一步就改變一個大小讓他去大於等於某段目前或者之後的區間
問說改動次數最多k次  改完後跟每次改動後他所負責的那段區間元素的差最小值為多少?
dp[i][j] : for the first i element, we used j operations. the minimum total space wasted 
會發現每次你要改動時都會有改動他可以cover的區間 那在他之前的最小值加上改動後的space wasted又可以構成新答案  -> dp
dp[i][j] = dp[s-1][j-1] + nums[s]*(i-s+1) - intervalSum;
                           wasteSpace
*/
