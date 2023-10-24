/*
787. Cheapest Flights Within K Stops
*/


//iterative TC:O(k*m) SC:O(k*n)
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {

        vector<vector<int>> dp(k+2, vector<int>(n, INT_MAX/2));
        dp[0][src] = 0; //當完全不能有中繼站 只有起點到起點是有效值
        int ret = INT_MAX/2;
        //可以中繼的次數
        for(int i = 1; i<=k+1; i++){
            for(auto flight:flights){
                int a = flight[0]; int b = flight[1]; int p = flight[2];
                dp[i][b] = min(dp[i][b], dp[i-1][a] + p);

                if(b == dst) ret = min(ret, dp[i][b]);
            }
        }
        return ret == INT_MAX/2 ? -1:ret;
    }
};

//優化空間->失敗

class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {

        vector<int> dp(n, INT_MAX/2);
        dp[src] = 0; //當完全不能有中繼站 只有起點到起點是有效值
        
        int ret = INT_MAX/2;
        //可以中繼的次數
        for(int i = 1; i<=k+1; i++){
            vector<int> temp(dp);
            for(auto flight:flights){
                int a = flight[0]; int b = flight[1]; int p = flight[2];
                dp[b] = min(dp[b], temp[a] + p);

                if(b == dst) ret = min(ret, dp[b]);
            }
        }
        return ret == INT_MAX/2 ? -1:ret;
    }
};


/*
此題是最小路徑和加上停止次數的限制 
可以用dijkstra or DP來做
DP的定義有點類似說 當你只能做一次飛機的時候dp[b]為多少 那兩次呢dp[b]為多少 
這個演算法 有個名稱叫鬆弛 relaxation 
dp[i][b]:定義為 能走i次的情況下可以走到b點的最小花費

dp[i][b] =min(dp[i-1][a] + price[a][b]) 因為走到b之前可能很多點都可以走到b 所以取其中最小值

*/
