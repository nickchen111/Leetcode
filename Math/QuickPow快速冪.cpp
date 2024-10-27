long long quickMul(long long a, long long b) {
    long long ans = 1;
    while(b) {
        if(b & 1) ans = (ans*a) % MOD;
        a = (a*a) % MOD;
        b >>= 1;
    }
}


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
          return (y*y%M)*x%M;
        }
        else return y*y%M;
    }

    double quickMul(double x, long long n) {
        if (n == 0) {
            return 1.0;
        }
        double y = quickMul(x, n / 2);
        return N % 2 == 0 ? y * y : y * y * x;
    }
};
