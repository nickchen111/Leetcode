/*
2767. Partition String Into Minimum Beautiful Substrings
*/

// TC:O(n^2) SC:O(n)
class Solution {
public:
    int minimumBeautifulSubstrings(string s) {
        unordered_set<int> set({1,5,25,125,625,3125,15625});

        int n = s.size();
        vector<int> dp(n+1, INT_MAX/2);
        s = "#" + s;
        dp[0] = 0;
        for(int i = 1; i <= n; i++){
            if(s[i] == '0') continue;
            int cur = 0;
            for(int j = i; j <= n; j++){
                cur = cur*2 + s[j]-'0';
                if(set.find(cur) != set.end()){
                    dp[j] = min(dp[j], dp[i-1] + 1);
                }
            }
        }

        return dp[n] >= INT_MAX/2 ? -1 : dp[n];
    }
};

/*
想求最少能切割出幾分binary string的數組讓裡面的十進位表示可以都是5的冪次
因為題目長度只到15 我們可以推論出5的密次有哪些
1,5,25,125,625,3125,15625
接著這題是要問切割字串數組那一類的並且切割後的答案會跟之前累積的數量有關 要想到用dp n^2來做
*/
