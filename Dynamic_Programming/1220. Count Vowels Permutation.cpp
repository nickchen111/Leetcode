/*
1220. Count Vowels Permutation
*/

//TC:O(n) SC:O(5*n)
class Solution {
public:
    int countVowelPermutation(int n) {
        vector<vector<long>> dp(n,vector<long>(5,0));
        long long M = 1e9+7;
        for(int j = 0; j<5; j++){
            dp[n-1][j] = 1;
        }

        for(int i = n-2; i>=0; i--){
            dp[i][0] = dp[i+1][1];
            dp[i][1] = (dp[i+1][0]+dp[i+1][2])%M;
            dp[i][2] = (dp[i+1][0]+dp[i+1][1]+dp[i+1][3]+dp[i+1][4])%M;
            dp[i][3] = (dp[i+1][2]+dp[i+1][4])%M;
            dp[i][4] = dp[i+1][0];
        }


        long res = 0;
        for(int j = 0; j<5; j++){
            res = (res+dp[0][j])%M;
        }

        return res;
    }
};

// TC:O(n) SC:O(10)
class Solution {
public:
    int countVowelPermutation(int n) {
        //優化空間
        vector<long> dp(5,0);
        long long M = 1e9+7;
        for(int j = 0; j<5; j++){
            dp[j] = 1;
        }

        for(int i = n-2; i>=0; i--){
            auto dp_temp = dp;
            dp[0] = dp_temp[1];
            dp[1] = (dp_temp[0]+dp_temp[2])%M;
            dp[2] = (dp_temp[0]+dp_temp[1]+dp_temp[3]+dp_temp[4])%M;
            dp[3] = (dp_temp[2]+dp_temp[4])%M;
            dp[4] = dp_temp[0];
        }


        long res = 0;
        for(int j = 0; j<5; j++){
            res = (res+dp[j])%M;
        }

        return res;
    }
};

/*
dp[i][0] = how many strings of [i:n-1] can be formed s[i] = a
dp[i][1] = how many strings of [i:n-1] can be formed s[i] = e
...
0:a
1:e
2:i
3:o
4:u

*/
