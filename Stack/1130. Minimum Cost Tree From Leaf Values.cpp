/*
1130. Minimum Cost Tree From Leaf Values
*/

// Stack+greedy TC:O(n) SC:O(n)
class Solution {
public:
    int mctFromLeafValues(vector<int>& arr) {
        int n = arr.size();
        vector<int> nextGreater(n,INT_MAX);
        vector<int> prevGreater(n,INT_MAX);
        stack<int> Stack;
        for(int i = 0; i<n; i++){
           while(!Stack.empty() && arr[Stack.top()] <= arr[i]){
               nextGreater[Stack.top()] = arr[i];
               Stack.pop();
           }    
           Stack.push(i);
        }

        while(!Stack.empty()) Stack.pop();

        for(int i = n-1; i>=0; i--){
            while(!Stack.empty() && arr[Stack.top()] < arr[i]){
               prevGreater[Stack.top()] = arr[i];
               Stack.pop();
           }    
           Stack.push(i);
        }

        int cost =0;
        for(int i =0; i<n; i++){
            int x = min(prevGreater[i],nextGreater[i]);
            if(x != INT_MAX){
                cost +=x*arr[i];
            }
        }
        
        return cost;
    }
};

// DP 區間寫法優化 TC:O(n^3) SC:O(n^2)
class Solution {
public:
    int mctFromLeafValues(vector<int>& arr) {
        int n = arr.size();
        vector<vector<int>> dp(n, vector<int>(n,INT_MAX/2));
        vector<vector<int>> mx(n, vector<int>(n));

        for(int i = 0; i < n; i++) {
            mx[i][i] = arr[i];
            if(i+1 < n) mx[i][i+1] = max(arr[i], arr[i+1]);
            for(int j = i + 2; j < n; j++) {
                mx[i][j] = max(arr[j], mx[i][j-1]);
            }
        }

        for(int i = 0; i < n; i++) {
            dp[i][i] = 0;
            if(i+1 < n) dp[i][i+1] = arr[i] * arr[i+1];
        }

        // for(int len = 3; len <= n; len++) {
        //     for(int i = 0; i + len - 1 < n; i++) {
        //         int j = i + len - 1;
        //         for(int k = i; k < j; k++) {
        //             dp[i][j] = min({dp[i][j], dp[i][k] + dp[k+1][j] + mx[i][k] * mx[k+1][j]});
        //         }
        //     }
        // }


        for(int j = 0; j < n; j++) {
            // x x x 
            for(int i = j-2; i >= 0; i--) {
                for(int k = i; k < j; k++) {
                    dp[i][j] = min({dp[i][j], dp[i][k] + dp[k+1][j] + mx[i][k] * mx[k+1][j]});
                }
            }
        }

        return dp[0][n-1];
    }
};

/*
x x x x x 
DFS(0,2) = min(DFS(0, DFS(1,2)), DFS(DFS(0,1),2))
dp[i][j] 此段區間的最小值為?
mx[i][j] 他的最大數字代表是?
*/

// DP TC:O(n^3) SC:O(n^2)
class Solution {
public:
    int mctFromLeafValues(vector<int>& arr) {
        int n = arr.size();
        auto dp = vector<vector<int>>(n,vector<int>(n,INT_MAX));
        auto large = vector<vector<int>>(n,vector<int>(n,INT_MIN));
        int sum = 0;
        for(int i = 0; i<n; i++){
            dp[i][i] = arr[i];
            large[i][i] = arr[i];
            sum+=arr[i];
        }

        for(int len = 2; len<=n; len++){
            for(int i = 0; i+len-1<n; i++){
                int j = i+len-1;
                for(int k = i; k<j; k++){
                    dp[i][j] = min(dp[i][j],dp[i][k]+dp[k+1][j]+large[i][k]*large[k+1][j]);
                    large[i][j] = max(large[i][k],large[k+1][j]);
                }
            }
        }
        return dp[0][n-1]-sum;
    }
};


/*
dp很好想 但要轉化成貪心 就會結合stack
為何會想到貪心呢  首先熟讀題目意思 可以理解每個數都會帶著一個大數去跟別人比較(剛開始的時候就是他自已)
為了要盡量最小化cost 會想找附近的最小的大數跟他相消 a*b + dp[i]+dp[j]的概念 其中dp[i]跟dp[j]你找誰相消都是固定的
但是如果遇到相同數字 就要有約定靠右邊的最大

6 5 4 4 4 5 -> 5 5 5 5 5 
6 5 4 -> 4 4 4 5
*/

 
