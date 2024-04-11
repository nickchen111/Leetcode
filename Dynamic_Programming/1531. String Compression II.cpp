/*
1531. String Compression II
*/

// TC:O(n^2*26*10) SC:O(n^2*26*10)
class Solution {
    int dp[101][101][27][11];
public:
    int getLengthOfOptimalCompression(string s, int K) 
    {
        // Handling the special case of "a...a" where there are 100 as
        if (s.size()==100 && K==0)
        {
            int flag = 1;
            for (int i=1; i<s.size(); i++)
            {
                if (s[i]!=s[0])
                {
                    flag = 0;                
                    break;
                }                    
            }
            if (flag==1) return 4;
        }
        
        int n = s.size();
        s = "#"+s;

        for (int i=0; i<=n; i++)
            for (int k=0; k<=K; k++)
                for (int ch=0; ch<=26; ch++)
                    for (int num=0; num<=10; num++)
                        dp[i][k][ch][num] = INT_MAX;
        // dp[i][k][ch][num]: the optimal solution for s[1:i]
        // with k digits removed, last letter as ch, the consecitive number of ch as num

        dp[0][0][26][0] = 0;

        for (int i=0; i<n; i++)
            for (int k=0; k<=min(K, i); k++)
                for (int ch = 0; ch <= 26; ch++)
                    for (int num = 0; num <=10; num++)
                    {
                        int cur = dp[i][k][ch][num];
                        //將不合法狀態pass
                        if (cur==INT_MAX) continue;

                        // delete s[i+1]
                        dp[i+1][k+1][ch][num] = min(dp[i+1][k+1][ch][num], cur);

                        // keep s[i+1]
                        if (s[i+1]-'a' == ch)
                        {
                            int add;
                            if (num==1) add = 1;  // a -> a2
                            else if (num>=2 && num<=8) add = 0; // a3->a4
                            else if (num==9) add = 1; // a9->a10;
                            else if (num==10) add = 0; // a10->a11;
                            dp[i+1][k][ch][min(num+1, 10)] = min(dp[i+1][k][ch][min(num+1, 10)], cur+add);
                        }
                        else
                        {
                            dp[i+1][k][s[i+1]-'a'][1] = min(dp[i+1][k][s[i+1]-'a'][1], cur+1);
                        }
                    }
        
        int ret = INT_MAX;
        for (int ch = 0; ch <= 26; ch++)
            for (int num = 0; num <=10; num++)                    
                ret = min(ret, dp[n][K][ch][num]);
        
        return ret;
    }
};

/*
通常做這類型刪減字串求最小最大題型 去切割字串的題目會想到dp[i][k] 走到i為止刪除了k個可以達到的最小長度
但是會忽略aabbaa這種情空 假設刪除的是bb 會發現答案不是a2a2應該要是a4所以這題還需要多兩個維度 最後出現的字母是啥 以及他連續出現的次數
有很多狀態是非法的
1.前五個字母刪掉八個
2. 前五個刪掉兩個最後以a結尾 但如果前五個都沒有a呢
所以不要去找之前有哪些狀態 dp還有另一種狀態轉移表達式 
用已知去看他能影響未來的哪些狀態
dp[i][k][ch][num] = dp[i+1][?][?][?]
1. we delete s[i+1]
    dp[i+1][k+1][ch][num]
2. we do not delete s[i+1]
    dp[i+1][k][s[i+1]-'a'][num+1 or 1看是否跟前面的一樣]
    num+1 要看前面是幾個 9 or 1這種的話長度才會變化
    1. if(num==1) add 1
    2. if(num == 2...8) add 0
    3. if(num == 9) add 1
    4. if(num == 10...98) add 0
    5. if(num == 99) add 1
ch = 26 特別給dp[0][0][26][0] = 0; 代表一開始沒字串的後狀態
*/
