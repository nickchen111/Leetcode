using LL = long long;
LL MOD = 1e9 + 7;
vector<LL> fac(n+1);
vector<LL> inv(n+1);
// 建造 階級的 fac 與逆元 
auto build = [&](LL limit) {
    fac[1] = 1;
    for(int i = 2; i <= limit; i++) {
        fac[i] = ((LL) i * fac[i-1]) % MOD;
    }

    inv[limit] = quickMul(fac[limit], MOD-2);
    for(int i = limit - 1; i >= 0; i--) {
        inv[i] = ((LL) (i+1) * inv[i+1]) % MOD;
    }
};
build(n);
long long quickMul(long long a, long long b) {
    long long ans = 1;
    while(b) {
        if(b & 1) ans = (ans*a) % MOD;
        a = (a*a) % MOD;
        b >>= 1;
    }

    return ans;
}

// 切記 comb cn取m 會是 n! / (m! * (n-m)!)
