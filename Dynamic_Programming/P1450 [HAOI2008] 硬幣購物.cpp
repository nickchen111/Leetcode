/*
P1450 [HAOI2008] 硬幣購物
*/

// TC:O(n * 15*3 + 4*m) m 為 target容量 n 為query次數 SC:O(m)
#include <iostream>
#include <vector>
using namespace std;
using LL = long long;
LL MOD = 1e9 + 7;
const LL LIMIT = 1e5;
LL dp[LIMIT+1];


int main() {
    int c1, c2, c3, c4, n;
    cin >> c1 >> c2 >> c3 >> c4 >> n;
    vector<int> coins = {c1, c2, c3, c4};
    vector<int> cnt(4);
    auto build = [&]() {
        dp[0] = 1;
        for (int i = 0; i < 4; i++) {
            for (int j = coins[i]; j <= LIMIT; j++) {
                dp[j] = dp[j] + dp[j-coins[i]];
            }
        }
    };

    build();
    auto query = [&](int s) {
        LL ilegal = 0;
        for(int status = 1; status <= 15; status++) {
            LL t = s;
            int sign = -1;
            for(int i = 0; i < 4; i++) {
                if((status >> i) & 1) {
                    t -= coins[i] *  (cnt[i]+1);
                    sign = sign*-1; // 偶數次的話就會是減法
                }
            }

            if(t >= 0) {
                ilegal += sign*dp[t];
            }
        }

        return dp[s] - ilegal;
    };

    int d1, d2, d3, d4, s;
    for (int i = 1; i <= n; i++) {

        cin >> d1 >> d2 >> d3 >> d4 >> s;
        cnt[0] = d1;
        cnt[1] = d2;
        cnt[2] = d3;
        cnt[3] = d4;
        cout << query(s) << endl;
    }

    return 0;
}

/*
這題問你，硬幣總共四種，每次你去逛商店，總共逛n次 n 最大1e5
你每次過去時，四個硬幣你帶的數量都不同，那麼每次過去時你可以組成的target數值的合法方案是多少種? ps target每次去也都會變
這題如果每次過去都跑一次dp 就會是 n * 4 * target 大概是 1e5 * 4 * 1e5 肯定超時
首先想到最簡單的就是不限定我物品數量能用多少個，這樣就是完全背包問題 dp[i]就是定義成 要達到i目標的話 有多少種方案數 在 物品數量無上限可重複用的狀態下
這時，你就可以去拆解說 因為我每次query 違規時的數量都不同，所以dp[i - 違規的數量*某物品價值] 就會搖身一變變成 此物品違規數量超過的狀況 詳情可見影片說明
https://www.youtube.com/watch?v=kBh4-ZvX6Hs&list=PLvKfL6GtwDxwuyrpAJfU3HTnPZl4WnraE&index=101
知道這點後就可以去對這四個物品做容斥，求出總共的違規狀況，然後就可以是 dp[target] - 違規數量 就會是答案!
求容斥的過程可以用狀態壓縮dp 去求
https://www.luogu.com.cn/problem/P1450
*/
