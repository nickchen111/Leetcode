/*
172. Factorial Trailing Zeroes
*/

// 寫法一
class Solution {
public:
    int trailingZeroes(int n) {
        int res = 0;
        long long divisor = 5;
        while(n >= divisor){
            res += n/divisor;
            divisor*=5;
        }

        return res;
    }
};

//寫法二
class Solution {
public:
    int trailingZeroes(int n) {
        if(n == 0) return 0;

        return n/5 + trailingZeroes(n/5);
    }
};

/*
兩種寫法 
1. 一層一層計算 可以提供幾個五的那些數字有幾個
ex: 除5 代表只能提供一個5
    除25 代表可以提供兩個5
    除5x5x5 = 125 可以提供三個5
2.遞歸調用 概念相同但是寫法不同而已
*/
