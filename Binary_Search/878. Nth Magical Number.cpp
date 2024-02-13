/*
878. Nth Magical Number
*/


// Two Pointer TC:O(k) SC:O(1)
class Solution {
    long M = 1e9+7;
public:
    int nthMagicalNumber(int n, int a, int b) {
        long LCM = lcm(a,b);
        //找週期 每個最小公倍數都是一個週期
        long p = n/(LCM/a + LCM/b - 1);
        long s = p*(LCM/a + LCM/b - 1);
        long t = (long)n - s;
        if(t == 0) return p*LCM%M;

        int i = 1, j = 1;
        int flag = 0;
        int count = 0;
        while(count < t){
            if(a*i < b*j){
                i++;
                flag = 0;
            }
            else{
                j++;
                flag = 1;
            }
            count++;
        }
        long remainder = 0;
        if(flag == 0) remainder = a*(i-1);
        else remainder = b*(j-1);
        
        return (LCM*p%M + remainder)%M;
    }
};

// BS TC:O(lgn) SC:O(1)
class Solution {
    using LL = long long;
    LL M = 1e9+7;
public:
    int nthMagicalNumber(int n, int a, int b) {
        LL x = lcm(a,b);

        LL left = 1; LL right = LLONG_MAX;

        while(left < right){
            LL mid = left + (right -left)/2;
            if(check(mid, x,a,b) >= n) {
                right = mid;
            }
            else left = mid + 1;
        }

        return left % M;
    }

    LL check(LL mid, LL x, LL a, LL b){
        LL res = mid/a + mid/b - mid/x;

        return res;
    }
};

/*
找到第n個能被 a or b整除的數字
最大公因數
2 4 6  8  10...
3 6 9 12 15...
最簡單就是用BS去找 然後數學的部分要理解在某個數以內的情況是藉由 mid/a + mid/b - mid/lcm 可以計算出
或者如果要找數字甚至超過64整型 也可以利用類似分而治之的概念算出他有多少個循環 然後看餘數次數用雙指針的方式去推論出在第幾個
*/
