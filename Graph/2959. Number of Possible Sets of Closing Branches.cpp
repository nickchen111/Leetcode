/*
2959. Number of Possible Sets of Closing Branches
*/

// Floyd + 狀態壓縮 TC:O(2^10*n^3) SC:O(n*n) 
class Solution {
public:
    int numberOfSets(int n, int maxDistance, vector<vector<int>>& roads) {

        int res = 0;
        for(int state = 0; state < (1<<n); state++){
            vector<vector<int>> dp(n, vector<int>(n,INT_MAX/3));
            for(int i = 0; i < n; i++){
                if(((state>>i)&1 )== 0) continue;//如果已經被去掉 就不理他
                dp[i][i] = 0;
            }

            //  一個邊一個邊加入 跟之前寫法不同的是 之前是一個點一個點加入
            for(auto road : roads){
                int a = road[0], b = road[1], cost = road[2];
                if(((state >> a)&1) == 0) continue;
                if(((state >> b)&1) == 0) continue;
                
                for(int  i = 0; i < n; i++){
                    if(((state >> i)&1) == 0) continue;
                    for(int j = 0; j < n; j++){
                        if(((state >> j)&1) == 0) continue;
                        dp[i][j] = min(dp[i][j], dp[i][a] + cost + dp[b][j]);
                        dp[i][j] = min(dp[i][j], dp[i][b] + cost + dp[a][j]);// 雙向的
                    }
                }
            }

            //判斷此刪除方式是否可行
            bool flag = 1;
            for(int i = 0; i < n; i++){
                if(((state >> i)&1) == 0) continue;
                for(int j = 0; j < n; j++){
                    if(((state >> j)&1) == 0) continue;
                    if(dp[i][j] > maxDistance){
                        flag = 0;
                        break;
                    }
                }
                if(flag == 0) break;
            } 
            if(flag) res += 1;
        }

        return res;
    }
};


/*
此題說一開始所有城市都有路可以連通 想刪掉一些 城市 來確保 每個城市之間走過去的成本小於等於 maxDistacne
只要暴力枚舉各種可能就好
1. 枚舉所有刪除方式 2^10 = 1024 -> 狀態壓縮方式去遍歷
2. Floyd n^3 去計算 每個點之間的最短距離 -> 10^3 都要用(state << i) & 1 == 0 來把被刪掉的點略過
3. 最後再遍歷一次 最短距離是否都合法 
*/
