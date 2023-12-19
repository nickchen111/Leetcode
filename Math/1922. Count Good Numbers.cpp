/*
1922. Count Good Numbers
*/

// TC:O(lgn) SC:O(lgn)
class Solution {
    using LL = long long;
    LL M = 1e9 + 7;
public:
    int countGoodNumbers(long long n) {
        LL numOfOdd = n/2;
        LL numOfEven = n/2 + n%2;
        return (power(5,numOfEven) * power(4,numOfOdd)) % M;
    }
    LL power(LL x, LL n){
        if(n == 0) return 1;

        LL res = power(x, n/2);
        res = res * res;
        res %= M;
        if(n % 2 == 1){
            res *= x;
            res %= M;
        }

        return res;
    }

};

/*
在偶數位上必須是偶數數字 -> 0 2 4 6 8 五個
奇數位上必須是質數 -> 2 3 5 7 四個
這是O(n)解法 把每一位數可能性相乘 但這題 n = 10^15 會超時...
如果n 為 偶數 那就會有 n/2 個 5 n/2  個 4
odd: n/2+1個 5 n/2個 4
*/
