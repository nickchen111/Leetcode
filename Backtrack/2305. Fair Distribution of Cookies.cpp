/*
2305. Fair Distribution of Cookies
*/

// 2024.12.18 狀壓DP TC:O(k * 3^n) SC:O(k * 2^n) 遞推的空間可以在優化 做到 2^n
class Solution {
public:
    int distributeCookies(vector<int>& cookies, int k) {
        int n = cookies.size();
        vector<int> sum((1<<n),0);
        for(int i = 0; i < (1<<n); i++) {
            for(int j = 0; j < n; j++) {
                if((i>>j) & 1) sum[i] += cookies[j];
            }
        }

        vector<vector<int>> dp(k, vector<int>(1<<n,0));
        dp[0] = sum;
        for(int i = 1; i < k; i++) {
            for(int j = 1; j < (1<<n); j++) {
                dp[i][j] = 1e9;
                for(int s = j; s; s = (s-1) & j) {
                    dp[i][j] = min(dp[i][j], max(dp[i-1][j^s],sum[s]));
                }
            }
        }

        return dp[k-1][(1<<n)-1];

        // for(int i = 0; i < n; i++) {
        //     for(int j = 0; j < (1<<i); j++) {
        //         sum[(1<<i) | j] = sum[j] + cookies[i];
        //     }
        // }
        // state = (1<<n) - 1 代表都選完了，問題在於分的狀態跟分了多少個小孩能達到的最小值是多少?

        /*
        遞歸 TC:O(k * 3^n) SC:O(k * 2^n)
        vector<vector<int>> memo((1<<n), vector<int>(k+1, -1));
        auto dfs = [&](auto &&dfs, int mask, int cnt) -> int {
            if(cnt == 1) return sum[mask];
            if(mask == 0) return 0;
            if(memo[mask][cnt] != -1) return memo[mask][cnt];
            int res = INT_MAX;
            int submask = mask;
            while(submask > 0) {
                int remain_mask = mask ^ submask;
                res = min(res, max(sum[submask], dfs(dfs, remain_mask, cnt-1)));
                submask = (submask-1) & mask;
            }
            return memo[mask][cnt] = res;
        };
        return dfs(dfs, (1<<n)-1, k);
        */
    }
};

// TC:O(lgM * n!) SC:(n!)
class Solution {
    int k;
public:
    int distributeCookies(vector<int>& cookies, int k) {
        //此即分配問題 並且將分配到最多的盡量最小化
        this->k = k;
        int n = cookies.size();
        sort(cookies.rbegin(),cookies.rend());
        int low = cookies[n-1];
        int high = accumulate(cookies.begin(),cookies.end(), 0);
        while(low < high){
            int mid = low + (high-low)/2;
            vector<int> child(k,0);
            if(backtrack(cookies,child,0,mid)){
                high = mid;
            }
            else low = mid+1;
        }

        return high;
    }

    bool backtrack(vector<int>& cookies, vector<int>& child, int cur, int th){
        //都分完了
        if(cur == cookies.size()) return true;

        bool flag = 0;
        for(int i = 0; i<k; i++){
            if(child[i]+cookies[cur] > th) continue;
            if(child[i] == 0){
                if(flag) return false;
                else flag = 1;
            }

            child[i]+=cookies[cur];
            if(backtrack(cookies,child,cur+1,th)) return true;
            child[i]-=cookies[cur];
        }

        return false;
    }
};
