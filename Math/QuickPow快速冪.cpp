class Solution {
long long M = 1e9+7;
public:
    //x為要做冪次的數字 n為冪次
    long long quickMul(long long x, long long n) {
        if (n == 0) {
            return 1;
        }
        LL y = quickMul(x, n / 2) % M;
        if(n%2){
          return y*y*x;
        }
        else return y*y;
    }

    double quickMul(double x, long long n) {
        if (n == 0) {
            return 1.0;
        }
        double y = quickMul(x, n / 2);
        return N % 2 == 0 ? y * y : y * y * x;
    }
};
