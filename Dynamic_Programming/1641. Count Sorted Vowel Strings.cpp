/*
1641. Count Sorted Vowel Strings
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int countVowelStrings(int n) {
        vector<vector<int>> dp(n, vector<int>(5));
        for(int j = 0; j < 5; j++){
            dp[0][j] = 1;
        }

        for(int i = 1; i < n; i++){
            for(int k = 0; k < 5; k++){
                for(int j = 0; j <= k; j++){
                    dp[i][k] += dp[i-1][j];
                }
            }
        }
        int res = 0;
        for(int k = 0; k < 5; k++){
            res += dp[n-1][k];
        }

        return res;
    }
};

//

1483. Kth Ancestor of a Tree Node

Status

Language
Runtime
Memory
Notes

Accepted
23 minutes ago
C++
0 ms
6.7 MB
Accepted
29 minutes ago
C++
3 ms
6.7 MB

nickchen11111
nickchen11111
Dec 06, 2023 20:53

Details
Solution
C++
Runtime
3 ms
Beats
30.30%
Memory
6.7 MB
Beats
22.37%
Click the distribution chart to view more details
Related Tags
Select related tags
0/5
class Solution {
public:
    int countVowelStrings(int n) {
        vector<int> dpa(n);
        vector<int> dpe(n);
        vector<int> dpi(n);
        vector<int> dpo(n);
        vector<int> dpu(n);
        dpa[0] = 1;
        dpe[0] = 1;
        dpi[0] = 1;
        dpo[0] = 1;
        dpu[0] = 1;
        for(int i = 1; i < n; i++){
            dpa[i] = dpa[i-1];
            dpe[i] = dpa[i-1] + dpe[i-1];
            dpi[i] = dpa[i-1] + dpe[i-1] + dpi[i-1];
            dpo[i] = dpa[i-1] + dpe[i-1] + dpi[i-1] + dpo[i-1];
            dpu[i] = dpa[i-1] + dpe[i-1] + dpi[i-1] + dpo[i-1] + dpu[i-1];
        }

        return dpa[n-1] + dpe[n-1] + dpi[n-1] + dpo[n-1] + dpu[n-1];
    }
};

/*
此題題意
給你一個字串的長度n 
字串只能包含母音 這樣的條件下可以組成多少個字典序排序過的合理組合
dpa[i] = dpa[i-1]
dpe[i] = dpa[i-1] + dpe[i-1]
...
*/
