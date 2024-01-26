/*
1316. Distinct Echo Substrings
*/

// Brute force TC:O(n^3) SC:O(n)
class Solution {
public:
    int distinctEchoSubstrings(string text) {
        int n = text.size();
        int res = 0;
        unordered_set<string> set;
        for(int i = 0; i < n; i++){
            for(int len = 1; i+len+len <= n; len++){
                string str1 = text.substr(i,len);
                string str2 = text.substr(i+len, len);
                if(str1 == str2 && set.find(str1) == set.end()){
                    res += 1;
                    set.insert(str1);
                }
            }
        }
        
        return res;
    }
};


// DP TC:O(n^2) SC:O(n)
class Solution {
    int dp[2005][2005];
public:
    int distinctEchoSubstrings(string text) {
        int n = text.size();
        unordered_set<string> set;
        int res = 0;
        text = "#" + text;
        for(int i = 1; i <= n; i++){
            for(int j = i+1; j <= n; j++){
                if(text[i] == text[j]){
                    dp[i][j] = dp[i-1][j-1] + 1;
                }
                if(dp[i][j] >= j-i){
                    string str = text.substr(i+1, j-i);
                    if(set.find(str) == set.end()){
                        res += 1;
                        set.insert(str);
                    }
                }
            }
        }

        return res;
    }
};

/*
找出一個字串中 能夠組成自己的substring有多少個 ex : abcabcddd -> abcabc 其中abc + abc = abcabc
我的想法是每走一個字就確定一次他跟之前有無重複長度只需走當下字的一半
n = 2000, 意味者時間複雜度為 n*n    還要再拆解字*n
*/
