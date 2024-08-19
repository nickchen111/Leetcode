/*
2478. Number of Beautiful Partitions
*/


// TC:O(n*k) SC:O(n*k)
class Solution {
    using LL = long long;
    LL M = 1e9+7;
public:
    int beautifulPartitions(string s, int k, int ml) {
        int n = s.size();
        vector<vector<LL>> dp(k+1, vector<LL>(n+1));
        dp[0][0] = 1;

        if(k*ml > n || !isPrime(s[0]) || isPrime(s[n-1])) return 0;

        for(int i = 1; i <= k; i++){
            int sum = 0;
            for(int j = i*ml; j + (k-i)*ml <= n; j++){
                // 確認之前的斷點是否合法 
                if(can_partition(s, j-ml)) sum = (sum + dp[i-1][j-ml]) % M;
                // 確認當前是否合法可以整併到後續的分類去
                if(can_partition(s, j)) dp[i][j] = sum;
            }
        }

        return dp[k][n];

    }

    bool isPrime(char ch){
        return ch == '2' || ch == '3' || ch == '5' || ch == '7';
    }
    bool can_partition(string& s, int j){
        return j == 0 || j == s.size() || !isPrime(s[j-1]) && isPrime(s[j]);
    }
};

/*
長度至少 minLength, 要分k組 
開頭要是prime 結尾要是非prime
問說要多少拆分方法
n = 1000

*/
