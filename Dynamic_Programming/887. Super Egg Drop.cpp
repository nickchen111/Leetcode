/*
887. Super Egg Drop
*/

//HG的解法 改變dp定義
//dp數組的範圍為何還是可以用n+1呢 目前想法是反正給我的次數越多 我可以計算出的樓層絕對不會比次數小
//TC:O(k*n) SC:O(k*n)
class Solution {
public:
    int superEggDrop(int k, int n) {
        vector<vector<int>> dp(k+1, vector<int>(n+1, 0));

        int m = 0;

        //將dp定義改為有k個雞蛋 最多可嘗試m次可以達到的最高高度
        while(dp[k][m] < n){
            m++;
            for(int i = 1; i<=k; i++){
                dp[i][m] = 1+dp[i-1][m-1]+dp[i][m-1];
            }
        }

        return m;
    }
};

// 正規寫法 dp+memo剪枝 會TLE 因為n 可以很大
//TC:O(k*n^2) SC:O(k*n) 因為子問題數量為 k*n(memo容器大小) 每個子問題會去遍歷樓層n 
class Solution {
    vector<vector<int>> memo;
public:
    int superEggDrop(int k, int n) {
        memo = vector<vector<int>>(k+1, vector<int>(n+1, INT_MIN));

        return dp(k,n);
    }

    int dp(int k, int n){
        if(k == 0) return 0;//代表我沒雞蛋了 測試完了 測試次數給0
        if(n <= 1) return n;
        if(k == 1) return n;
        if(memo[k][n] != INT_MIN) return memo[k][n];

        //遍歷選擇在每個樓層往下丟的結果 取最小值 但是是取破與不破的最大值中的最好那個(最小值)
        int ans= INT_MAX;
        for(int i = 1; i<=n; i++){//樓層
            ans = min(ans, 1+max(dp(k-1,i-1), dp(k,n-i)));
        }

        return memo[k][n] = ans;
    }
};

//將遍歷子問題時的時間優化
//TC:O(k*n*lgn) SC:O(k*n)
class Solution {
    vector<vector<int>> memo;
public:
    int superEggDrop(int k, int n) {
        memo = vector<vector<int>>(k+1, vector<int>(n+1, INT_MIN));

        return dp(k,n);
    }

    int dp(int k, int n){
        if(k == 0) return 0;//代表我沒雞蛋了 測試完了 測試次數給0
        if(n <= 1) return n;
        if(k == 1) return n;
        if(memo[k][n] != INT_MIN) return memo[k][n];

        //因為發現破掉的狀況dp數組會呈現單調遞增i-1 而沒破的狀況會呈現單調遞減with increasing i: n-i
        //用二分搜索
        int l = 1;
        int r = n;
        while(l<r){
            int m = l + (r-l)/2;//會選左邊
            int broken = dp(k-1,m-1);
            int unbroken = dp(k, n-m);
            if(broken >= unbroken){
                r=m;
            }
            else l = m+1;
        }
        
        return memo[k][n] = 1+dp(k-1, l-1);//因為比較到真正l == r時 一定是這個最大 or跟單調遞減的那個相等 
    }
};

/*
HG：
此题网上可以搜索到的解法是:令dp[k][n]表示用k个鸡蛋来测试n层楼,需要用的最少的trial次数.这种定义是和题意一致的.动态转移方程是:
dp[k][n] = min_i {max(dp[k-1][i-1],dp[k][n-i])+1}  for i =1,2,...,n (+1是因为0 index)
基本思想是我们考虑将一个蛋放在第i层去实验.如果碎了,那么我们只能继续尝试dp[k-1][i-1];如果没有碎,那么我们相当于可以继续用k个蛋去尝试第i层以上共N-i层楼的实验.但这种遍历n的循环非常耗时,因为n可以非常大.

另一种巧妙的解法是改变状态的定义,令dp[k][m]表示用k个鸡蛋和m次尝试,最多可以测试的楼层的高度.那么转移方程是:
dp[k][m] = dp[k-1][m-1]+dp[k][m-1]+1
这个思想是,我们设x=dp[k-1][m-1],那么我们在第x+1层扔一个鸡蛋:如果碎了,我们就用(k-1,m-1)的策略,能测量的楼层仍然是x.如果没碎,我们就能在x+1层之上,用(k,m-1)的策略,再检测x2 = dp[k][m-1]层楼.所以总的来说,高度在x1+1+x2之内的楼层,我们必然都可以通过(k,m)来实现检测.
*/



