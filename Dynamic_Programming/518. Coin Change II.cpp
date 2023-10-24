/*
518. Coin Change II
*/

//TC:O(n*amount) SC:O(n*amount)
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        int n = coins.size();

        //dp 定義為 目前有i種硬幣可選擇可以組合出amount的方式有哪些
        vector<vector<int>> dp(n+1, vector<int>(amount+1, 0));
        //base case
        for(int i = 0; i<=n; i++){
            dp[i][0] = 1;
        }

        //狀態轉移方程
        for(int i = 1; i <=n; i++){//遍歷選擇
            for(int sum = 1; sum<=amount; sum++){//容量
                if(sum >= coins[i-1]){
                    dp[i][sum] = dp[i-1][sum]+dp[i][sum-coins[i-1]];//選跟不選的狀態 
                    //後者dp[i]代表還是在重複使用的條件下->符合完全背包
                } 
                else dp[i][sum] = dp[i-1][sum];//代表不能選 目前面額超過
            }
        }

        return dp[n][amount];
    }
};

//把重複的次數寫出來
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        //背包問題 但是可以重複使用
        int n = coins.size();
        coins.insert(coins.begin(), 0);
        vector<int> dp(amount+1, 0);
        dp[0] = 1;

        for(int i = 1; i<=n; i++){
            auto dp_temp = dp;
            for(int x = 1; x<=amount; x++){
                dp[x] = 0;
                for(int k = 0; k <= x/coins[i]; k++)
                    if(x-k*coins[i] >= 0)
                        dp[x] += dp_temp[x-k*coins[i]];// 選or不選 且後者包含可以重複選用之意
            }
        }

        return dp[amount];
    }
};


//優化 空間壓縮 TC:O(n*amount) SC:O(amount)

class Solution {
public:
    int change(int amount, vector<int>& coins) {
        int n = coins.size();

        //dp 定義為 目前有i種硬幣可選擇可以組合出amount的方式有哪些
        vector<int> dp(amount+1);
        //base case
        dp[0] = 1;


        //狀態轉移方程
        for(int i = 0; i <n; i++){//遍歷選擇
            for(int sum = 1; sum<=amount; sum++){//容量
                if(sum >= coins[i]){
                    dp[sum] = dp[sum]+dp[sum-coins[i]];//選跟不選的狀態 
                    //後者dp[i]代表還是在重複使用的條件下->符合完全背包
                } 
                else dp[sum] = dp[sum];//代表不能選 目前面額超過 這行其實可以刪除
            }
        }

        return dp[amount];
    }
};

//優化的極致
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        //背包問題 但是可以重複使用
        int n = coins.size();
        coins.insert(coins.begin(), 0);
        vector<int> dp(amount+1, 0);
        dp[0] = 1;

        for(int i = 1; i<=n; i++){
            for(int x = 1; x<=amount; x++){
                if(x-coins[i] >= 0)
                    dp[x] += dp[x-coins[i]];// 選or不選 且後者包含可以重複選用之意
            }
        }

        return dp[amount];
    }
};


/*
與之前題型不一樣的是之前問你 可以有最少幾個零錢湊出 現在問你他可以有幾種湊法
他有點類似完全背包問題：外層包容量 內層包選擇 然後用+=的方式把答案累加起來 
但是這樣會有個問題是相同的元素 不同的排列組合會被重複計算
ex: 1 2 5, 5 2 1 一樣元素不同排序但會被當成兩個
HG寫法：
要改成01背包問題的方式外層包選擇 內層包容量 裡面再包一層可重複次數來做累加計算
優化方式的話就是不另外用dp_temp來儲存上一個循環的答案 直接用一個Dp做到底
dp[i][c]: 到第i個物件為只要組成sum:c有幾種方法

LA大：
直接想dp[i][c] = dp[i-1][c]不用跟+ dp[i][c-nums[i]];用
我覺得直觀上用完全背包問題(la大)去想最能夠理解
*/
