/*
552. Student Attendance Record II
*/


// TC:O(n) SC:O(n)
class Solution {
    using LL = long long;
    LL M = 1e9+7;
public:
    int checkRecord(int n) {
        vector<LL> dp00(n+1);
        vector<LL> dp01(n+1);
        vector<LL> dp02(n+1);
        vector<LL> dp10(n+1);
        vector<LL> dp11(n+1);
        vector<LL> dp12(n+1);
        dp00[0] = 1; //empty
        dp01[0] = 0;
        dp02[0] = 0;
        dp10[0] = 0;
        dp11[0] = 0;
        dp12[0] = 0;
        for(int i = 1; i <= n; i++){
            dp00[i] = (dp01[i-1] + dp00[i-1] + dp02[i-1])%M;
            dp01[i] = dp00[i-1]%M;
            dp02[i] = dp01[i-1]%M;
            dp10[i] = (dp00[i-1] + dp10[i-1] + dp01[i-1] + dp02[i-1] + dp11[i-1] + dp12[i-1])%M;
            dp11[i] = dp10[i-1]%M;
            dp12[i] = dp11[i-1]%M;
        }

        return (dp00[n] + dp01[n] + dp02[n] + dp10[n] + dp11[n] + dp12[n])%M;
    }
};


/*
學生能獲獎條件
1. 沒有缺席 或者只缺一次 < 1
2. 從未遲到超過連續3天 代表2天是極限 <= 2
給定一出缺席表長度n 問有幾種表達是可以獲獎的

HG: 
先處理第一個條件
dp0[i] = dp0[i-1]*2; 可以是L or P
dp1[i] = dp0[i-1]*1 + dp1[i-1]*2;

dp0[n] + dp1[n] ->ans
處理第二個條件 
dp0[i] = (dp0[i-1] + dp1[i-1] + dp2[i-1])*2; 截止i的時候i本身不是L可以有的合法字符串
dp1[i] = dp0[i-1]*1;
dp2[i] = dp1[i-1]*1;

所以3*2有六種狀態
dp00[i] for s[0:i] never A apeared, ending with 0 L 
dp01[i] for s[0:i] never A apeared, ending with 1 L 
dp02[i] for s[0:i] never A apeared, ending with 2 L 
dp10[i] for s[0:i]  A apeared once, ending with 0 L 
dp11[i] for s[0:i]  A apeared ocne, ending with 1 L 
dp12[i] for s[0:i]  A apeared once, ending with 2 L

dp00[i] = dp01[i-1]*'L' + dp00[i-1]*'P' + dp02[i-1]*'P';
dp01[i] = dp00[i-1]*'L';
dp02[i] = dp01[i-1]*'L';
dp10[i] = dp00[i-1]*'A' + dp10[i-1]*'P' + dp01[i-1]*'A' + dp02[i-1]*'A' + dp11[i-1]*'P' + dp12[i-1]*'P';
dp11[i] = dp10[i-1]*'L';
dp12[i] = dp11[i-1]*'L';
*/
