// TC:O(n^2) SC:O(n)
class Solution {
    using ll = long long;
public:
    long long minimumCost(vector<int>& nums, vector<int>& cost, int k) {
        /*
        問說可以切割數組任意份，每次切割完後他的代表大小就是 0 ~ 目前這個數字 + k * (i + 1) * cost(區間l ~ r) 問說這樣的話最小值是多少
        感覺是劃分型DP + 前綴和處理 但是會是n^3 需要優化
        該怎麼快速判斷出前面要抓哪個數字
        dp[i-1][l] + (presum_n[j+1] + (ll)k * i) * (presum_c[j+1] - presum_c[l])
        變數: dp[i-1][l], - presum_c[l]
        dp[i-1][l] - (presum_n[j] + k * i) * presum_c[l] 這段取最小 
        應該這樣拆分formula:
        dp[i-1][l] + (presum_n[j+1] + (ll)k * i) * (presum_c[j+1] - presum_c[l]) = 
        dp[i-1][l] + (presum_c[j+1] - presum_c[l]) * presum_n[j+1] + k * i * presum_n[j+1]
        這題引入了了一個LC從來沒考過的知識點:帶權子數組和->可以等於k個後綴和 過程不同但是總和相同, 如此就可以把變量i均分出來
        */
        int n = nums.size();
        vector<ll> presum(n+1);
        partial_sum(cost.begin(), cost.end(), presum.begin() + 1); // 可以學一下這種庫函數計算前綴和
        
        vector<ll> dp(n+1, LLONG_MAX/2);
        dp[0] = 0;
        ll sum = 0;
        for(int i = 0; i < n; i++) {
            sum += (ll) nums[i];
            for(int j = 0; j <= i; j++) {
                dp[i+1] = min(dp[i+1], dp[j] + sum * (presum[i+1] - presum[j]) + k * (presum[n] - presum[j]));
            }
        }
        return dp[n];
        /*
        遞推 O(n^3)
        vector<ll> dp(n+1, vector<ll>(dp, LLONG_MAX/2));
        dp[0][0] = 0;
        for(int i = 1; i <= n; i++) {
            // 目前起點開始走能有的最小值
            
            for(int j = i-1; j < n; j++) {
                for(int l = j; l >= 0; l--) {
                    dp[i][j+1] = min(dp[i][j+1], dp[i-1][l] + (presum_n[j+1] + (ll)k * i) * (presum_c[j+1] - presum_c[l]));
                }
            }
        }
        for(int j = 1; j <= n; j++) ans = min(ans, dp[j][n]);
        return ans;
        */
        /*
        遞歸 O(n^3)
        vector memo(n, vector<ll>(n+1, LLONG_MAX/2));
        auto dfs = [&](auto &&dfs, int i, int cnt) -> ll {
            if (i == n) return 0;
            ll &ret = memo[i][cnt];
            if(ret != LLONG_MAX/2) return ret;
            for(int j = i; j < n; j++) {
                ret = min(ret, dfs(dfs, j+1, cnt + 1) + (presum_n[j+1] + k * cnt) * (presum_c[j+1] - presum_c[i]));
            }
            return ret;
        };
        return dfs(dfs, 0, 1);
        */
    }
};
