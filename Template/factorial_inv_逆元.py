n = len(nums)
fac = [0] * (n+1)
fac[0] = 1
for i in range(1, n+1):
    fac[i] = fac[i-1] * i % MOD
inv = [0] * (n+1)
inv[-1] = pow(fac[-1], -1, MOD)
for i in range(n-1, -1, -1):
    inv[i] = inv[i+1] * (i+1) % MOD
