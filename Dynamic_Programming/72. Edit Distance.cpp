/*
72. Edit Distance
*/

//迭代解法
class Solution {
    //自底向上
public:
    int minDistance(string word1, string word2) {
        int m = word1.size();
        int n = word2.size();
        vector<vector<int>> dp(m+1, vector<int>(n+1));//要顧及到兩個都走到底的狀態是不用更改次數的
        //base case
        for(int i = 1; i<=m; i++){
            dp[i][0] = i;
        }
        for(int j = 1; j<=n; j++){
            dp[0][j] = j;
        }

        //狀態轉移方程
        for(int i = 1; i<=m; i++){//定住i的位置 ＠word1 上 去看是否有跟word2各種j相同
            for(int j = 1; j<=n; j++){
                if(word1[i-1] == word2[j-1]){
                    dp[i][j] = dp[i-1][j-1]; //相同代表兩個可以直接在往後移根本不用增刪改動作
                }
                else{
                    dp[i][j] = min(
                        dp[i][j-1]+1,    //新增插入一個
                        dp[i-1][j]+1, // 刪除
                        dp[i-1][j-1]+1 //直接改 替換掉
                    );
                }
            }
        }
        return dp[m][n];
        
    }
    int min(int a, int b, int c){
        return std::min(a, std::min(b, c));
    }
};

//自頂向下 多了memo 時間快好多 tc 100% 
class Solution {
    //自頂向下
public:
    int minDistance(string word1, string word2) {
        int m = word1.size();
        int n = word2.size();
        vector<vector<int>> memo(m+1, vector<int>(n+1, -1));
        return backtrack(word1, word2, m, n, memo);
    }
    int backtrack(string& word1, string& word2, int m, int n, vector<vector<int>>& memo){
        if(m == 0) return memo[m][n] = n;
        if(n == 0) return memo[m][n] = m;

        //如果有遇到過的話
        if(memo[m][n] != -1) return memo[m][n];

        //開始處理相同不同的情況
        if(word1[m-1] == word2[n-1]){
            return memo[m][n] = backtrack(word1, word2, m-1, n-1, memo);
        }
        else{
            int insertChar = backtrack(word1, word2, m, n-1, memo)+1;
            int deleteChar = backtrack(word1, word2, m-1, n, memo)+1;
            int replaceChar = backtrack(word1, word2, m-1, n-1, memo)+1;
            
            return memo[m][n] = min(insertChar, deleteChar, replaceChar);
        }
    }
    int min(int a, int b, int c){
        return std::min(a, std::min(b, c));
    }
};



/*
解題思路：
解決兩個字符串的動態規劃問題大部份是用two pointer去指向他
有兩種寫法
1.自頂向下
2.自底向上 
思考選擇 狀態 dp數組定義 base case
dp數組定義： dp[i][j] 從word1[0...i] 改到word2[0....j]要多少步驟
tc: o(m*n) sc:o(m*n)
*/
