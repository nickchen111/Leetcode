/*
576. Out of Boundary Paths
*/

// tc: O(k*m*n) sc: O(2*m*n)
class Solution {
public:
    int findPaths(int m, int n, int maxMove, int startRow, int startColumn) {
        auto dp = vector<vector<int>>(m, vector<int>(n,0));
        auto temp = dp;
        int M = 1e9+7;

        for(int k =0; k<maxMove; k++){//總共走k步從1~k
            //不斷更新dp合法範圍的可能性
            for(int i = 0; i<m; i++){
                for(int j = 0; j<n; j++){
                    long a = (i-1 < 0)? 1:dp[i-1][j];//往上來的可能性
                    long b = (j-1 < 0)? 1:dp[i][j-1];//往左來的可能性
                    long c = (i+1 == m)? 1:dp[i+1][j];//往下來的可能性
                    long d = (j+1 == n)? 1:dp[i][j+1];//往右來的可能性

                    temp[i][j] = (a+b+c+d)%M; //因為會怕影響到裡面還在run的判斷 所以不能改dp
                }
            }
            dp = temp; 
        }

        return dp[startRow][startColumn];
    }
};

/*
這題有點難想 
主要是倒過來想從出界的地方走到裡面每格會有幾種可能
從只走一步開始 到可以走K步 每一次都在更新裡面的dp數組 更新完才能去做疊加得到有可能走到的可能性

考點
1.能否想到倒過來想走到原點
2.每一步的可能性都是由他的減一步貢獻來的
*/
