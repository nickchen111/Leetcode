// 用這個
long long quickMul(long long a, long long b) {
    long long ans = 1;
    while(b) {
        if(b & 1) ans = (ans*a) % MOD;
        a = (a*a) % MOD;
        b >>= 1;
    }

    return ans;
}


class Solution {
long long MOD = 1e9+7;
public:
    //x為要做冪次的數字 n為冪次
    long long quickMul(long long x, long long n) {
        if (n == 0) {
            return 1;
        }
        LL y = quickMul(x, n / 2) % MOD;
        if(n%2){
          return (y*y%MOD)*x%MOD;
        }
        else return y*y%MOD;
    }

    double quickMul(double x, long long n) {
        if (n == 0) {
            return 1.0;
        }
        double y = quickMul(x, n / 2);
        return N % 2 == 0 ? y * y : y * y * x;
    }
};
