/*
2976. Minimum Cost to Convert String I
*/


// TC:O(n^3 + m) SC:O(n^2) n 為26
class Solution {
    using LL = long long;
public:
    long long minimumCost(string source, string target, vector<char>& original, vector<char>& changed, vector<int>& cost) {
        
        int n = changed.size();
        vector<vector<int>> dp(26, vector<int>(26,INT_MAX/3));
        for(int i = 0; i < 26; i++){
            dp[i][i] = 0;
        }
        
        for(int i = 0; i < n; i++){
            int a = original[i] - 'a';
            int b= changed[i] - 'a';
            dp[a][b] = min(dp[a][b], cost[i]);
        }
        
        for(int k = 0; k < 26; k++){
            for(int i = 0; i < 26; i++){
                for(int j = 0; j < 26; j++){
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
                }
            }
            
        }
        
        LL res = 0;
        int m = source.size();
        for(int i = 0;  i < m ; i++){
           if(source[i] != target[i]){
               int a = source[i] - 'a';
               int b= target[i] - 'a';
               LL dist = dp[a][b];
               if(dist == INT_MAX/3) return -1;
               else res += dist;
           }
        }
        
        return res;
        
    }
};

/*
此題重點在於如何先將graph轉出來 判斷出從某點到某點的最短距離
如果要求所有點到所有點的最短距離 毫無疑問floyd 不能用Dijkstra Dijkstra比較適合用在只求某點到所有點最短距離
*/
