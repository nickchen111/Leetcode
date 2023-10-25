/*
50. Pow(x, n)
*/


// Iterative TC:O(lgn) SC:O(1)
class Solution {
public:
    double myPow(double x, int n) {
        //第一種方法 iterative 處理
        bool negative = false;
        if(n < 0){
            x = 1/x;
            negative = true;
            n = -(n+1);//怕負數取到正的時候溢出-2^31 <= n <= 2^31-1
        }
        double res = 1;
        double temp = x;
        while(n != 0){
            //不論是奇數還是偶數狀況 最後的時候都會變成n = 1
            if(n%2 == 1){
                res*=temp;
            }
            //將次方除以二 相對應的temp也要乘上自己
            temp*=temp;
            n/=2;
        }

        if(negative){
            res*=x;
        }

        return res;
    }
};

//Bit Manipulation TC:O(lgn) SC:O(1)
class Solution {
public:
    double myPow(double x, int n) {
        //Bit manipulation
        double res =1;
        long absN = abs(n);
        while(absN > 0){
            //確認二進位中是否還有1
            if(absN & 1) res*=x;
            absN >>=1;
            x*=x;
        }

        return (n < 0) ? 1/res:res;
    }
};
