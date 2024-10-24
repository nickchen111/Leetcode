/*
1312. Minimum Insertion Steps to Make a String Palindrome
*/

// 最佳化 不要用長度寫法去寫 TC:O(n^2) SC:O(n^2)
class Solution {
public:
    int minInsertions(string s) {
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n,INT_MAX/2));
        for(int i = n - 1; i >= 0; i--) {
            dp[i][i] = 0;
            if(i-1 >= 0) {
                if(s[i] == s[i-1]) {
                    dp[i-1][i] = 0;
                }
                else dp[i-1][i] = 1;
            }
            for(int j = i + 2; j < n; j++) {
                if(s[i] == s[j]) {
                    dp[i][j] = dp[i+1][j-1];
                }
                else dp[i][j] = min(dp[i][j-1], dp[i+1][j]) + 1;
            }
        }

        return dp[0][n-1];
    }
};


//用SCS概念做 
class Solution {
    //SCS
public:
    int minInsertions(string s) {
        int n = s.size();
        string t = s;
        reverse(t.begin(), t.end());
        //開始找兩者的SCS
        vector<vector<int>> dp(n+1, vector<int>(n+1, 0));

        //想一下base case 當某個string是零 那麽最短共同子序列就是另一個序列本身
        for(int i = 0; i<=n; i++){
            dp[i][0] = i;
            dp[0][i] = i;
        }

        for(int i = 1; i<=n; i++){
            for(int j = 1; j<=n; j++){
                if(s[i-1] == t[j-1]){//兩個字符一樣
                    dp[i][j] = dp[i-1][j-1]+1;//回文串長度
                }
                else{
                    dp[i][j] = min(dp[i-1][j]+1, dp[i][j-1]+1);//加一就是把沒有被算進去的那項不同項在加上去
                }
            }
        }
        return dp[n][n]-n; //依照題目要求是要更改的長度 dp[n][n]為最後出來的SCS長度 減去原本長度就會是他要加上多少次的次數
    }
};

//區間回文串
class Solution {
    //區間回文串技巧
public:
    int minInsertions(string s) {
        int n = s.size();

        vector<vector<int>> dp(n, vector<int>(n, 0)); //定義為 s[i:j]要變回文串需要經過幾次insert操作
        //base case
        for(int i = 0; i<n; i++){
            dp[i][i] = 0; //只有一個字符的狀況 包含沒字符的狀態
        }

        for(int i = 0; i+1<n; i++){ //兩個字符的狀況
            dp[i][i+1] = (s[i]==s[i+1]) ? 0:1;
        }

        for(int len = 3; len<=n; len++){
            for(int i = 0; i+len-1<n; i++){//頭
                int j = i+len-1;//尾巴 減一為了變index
                if(s[i] == s[j]){
                    dp[i][j] = dp[i+1][j-1];//只需要加入一個字符即可
                }
                else{
                    dp[i][j] = min(dp[i+1][j]+1, dp[i][j-1]+1);
                }
            }
        }
        return dp[0][n-1];
    }
};

/*
解題思路：
要插入幾次可以讓一個string變成回文串
1.用區間回文串dp技巧
dp[i][j]:  the minimum number of steps to make s[i:j] palindrome.
特別需要注意區間edge狀況
如果用這種技巧 直接讓dp[i][j]是index會更好 因為肯定會是 i+1 j j-1 i這種的不會有越界情況
tc: o(n^2) sc: o(n^2)

2.創建一個reverse字串 求兩個之間的SCS 其SCS就會是各自的最短回文串  做法跟LCS類似
leetcode - > 自己的回文串會是 leetcodedocteel
edodteel ->  自己的回文串會是 leetcodedocteel
求兩者的SCS(shortest common supersequence) 就會是各自的回文串一樣結果
dp[i][j] 求 s[0:i] t[0:j] 之間 回文串長度 
tc: o(n^2) sc: o(n^2)

HG思路：
解法1：
第一种方法是：我们将原数列s逆序得到t。本题的答案等同于求这两个字符串的shortest common supersequence (SCS)。
这个转换其实并不容易理解。我们只能大概地有一种直观的感受：因为s和t是逆序关系，s最后一个字符等于t的第一个字符，应该让s放置于t的前面，
尽可能地重合s的尾部和t的头部来提高字符重用的利用效率。所以最终s和t的SCS应该是个回文串。既然SCS的第一个S是shortest的意思，那么这个SCS就是通过s可以得到的最短的回文串。
这么转换之后，本题就是1092.Shortest-Common-Supersequence.

解法2：
另一种更容易理解和想到的方法是区间型DP：定义dp[i][j]表示区间s[i:j]变成回文串最少需要多少添加多少字符。状态转移方程很容易理解：
if (s[i]==s[j])  
  dp[i][j]=dp[i+1][j-1]; 
else 
  dp[i][j] = min(dp[i+1][j]+1,dp[i][j-1]+1) 
  // 前者表示让s[i+1:j]已经成为回文串，再在s[j]后添加一个与s[i]相同的字符使得s[i:j]变成回文串
  // 前者表示让s[i:j-1]已经成为回文串，再在s[i]前添加一个与s[j]相同的字符使得s[i:j]变成回文串
*/
