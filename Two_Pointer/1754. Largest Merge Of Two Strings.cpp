/*
1754. Largest Merge Of Two Strings
*/

// TC:O(n^2) SC:O(1)
class Solution {
public:
    string largestMerge(string word1, string word2) {
        int p1 = 0, p2 = 0;
        int m = word1.size();
        int n = word2.size();
        string res;
        while(p1 < m && p2 < n){
            if(word1[p1] > word2[p2]){
                res += word1[p1];
                p1++;
            }
            else if(word1[p1] < word2[p2]){
                res += word2[p2];
                p2++;
            }
            else {
                string str1 = word1.substr(p1);
                string str2 = word2.substr(p2);
                if(str1 > str2){
                    res += word1[p1];
                    p1++;
                }
                else {
                    res += word2[p2];
                    p2++;
                }
            }
        }

        while(p1 < m){
            res += word1[p1];
            p1++;
        }
        while(p2 < n){
            res += word2[p2];
            p2++;
        }

        return res;
    }
};


/*
從兩個字串的頭開始構築出新的字串 能構築出的字典序最大的字串為何
dp[i][j] : max(dp[i-1][j] + word2[i-1], dp[i][j-1] + word2[j])  看最後一個字誰大就選誰
但是這個方式string[3000][3000] 空間複雜度會是 3e3*3e3*6e3會MLE...
改用雙指針+greedy 這題遇到word[i] == word[j]會不知道該選誰 這時候就是比較誰的後續字典序比較大優先取誰
因為他比較大 所以肯定會先讓較大的字母優先露出 相對有利
ehc
ehb
eheh"c"b
acg
acc
ac"g"acc
*/
