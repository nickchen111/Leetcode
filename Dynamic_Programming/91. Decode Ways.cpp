/*
91. Decode Ways
*/

//9/13 覺得比較容易理解的寫法
class Solution {
public:
    int numDecodings(string s) {
        int n = s.size();
        vector<int> dp(n+1, 0);
        s = "#"+s;
        dp[0] = 1;
        dp[1] = s[1] == '0' ? 0:1;
        for(int i = 2; i<=n; i++){
            int j = s[i]-'0'; int k = s[i-1]-'0';
            if(s[i] != '0') dp[i] += dp[i-1];

            if(10 <= k*10+j && 26>= k*10+j){
                dp[i]+=dp[i-2];
            }

        }

        return dp[n];
    }
};

//dp tc: o(n) sc:o(n)
class Solution {
public:
    int numDecodings(string s) {
        int n = s.size();
        if(n == 0) return 0;

        vector<int> dp(n+1);
        dp[0] = 1; //為了第二位有可能可以湊成一個數
        dp[1] = s[0] == '0' ? 0:1;
        
        //dp數組跟s差一個index
        for(int i = 2; i<=n; i++){
            char c = s[i-1]; char d = s[i-2];
            if(c-'0' >=1 && c-'0' <= 9){
                dp[i] +=dp[i-1];
            }
            int num = (d-'0')*10 + (c-'0');
            if(num >= 10 && num <= 26){
                dp[i] +=dp[i-2];
            }
        }

        return dp[n];
    }
};

//優化dp空間 結果beat 100% 94% tc: o(n) sc:o(1)
class Solution {
    //優化看看
public:
    int numDecodings(string s) {
        int n = s.size();
        if(n == 0) return 0;

        
        int w1 = 1; 
        int w2 = s[0] == '0' ? 0:1;
        
        //dp數組跟s差一個index
        for(int i = 1; i<n; i++){
            int w = 0;
            char c = s[i]; char d = s[i-1];
            if(c-'0' >=1 && c-'0' <= 9){
                w+=w2;
            }
            int num = (d-'0')*10 + (c-'0');
            if(num >= 10 && num <= 26){
                w+=w1;
            }
            w1 = w2;
            w2 = w;
        }

        return w2;
    }
};


/*
dp[i]代表 s[0:i]可以被解密成最多多少種情況
每次的結果取決於前一次跟前前一次之間能不能再被當成一個字母
*/
