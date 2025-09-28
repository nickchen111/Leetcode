# TC:O(n * (r - l + 1)) SC:O(r - l + 1)
class Solution:
    def zigZagArrays(self, n: int, l: int, r: int) -> int:
        '''
        長為n, l ~ r 範圍, 兩個相鄰ele皆不同, 沒有任三個數字組成遞增 or 遞減 代表必須要是波峰or波谷
        問說有多少個這樣的array
        dp !?
        走到i為止前一個填某數字 當下可以填啥 所能得到的數量
        之前是遞增or遞減 當下走到某個數字可以獲得的組合量
        '''
        MOD = 10 ** 9 + 7
        m = r - l + 1

        f0 = [1] * m
        f1 = [1] * m
        for _ in range(n - 1):
            pre = 0
            for i, v in enumerate(f1):
                f1[i] = pre % MOD
                pre += v

            suf = 0
            for i in range(m - 1, -1, -1):
                v = f0[i]
                f0[i] = suf % MOD
                suf += v

            f0, f1 = f1, f0
        return (sum(f0) + sum(f1)) % MOD


        '''
        Naive解法
        dp_inc = [1] * m
        dp_dec = [1] * m
        
        # for x in range(m):
        #     dp_inc[x] = x
        #     dp_dec[x] = (m - 1 - x)
        for i in range(n - 1):
            # pre_inc = [0] * (m + 1)
            # pre_dec = [0] * (m + 1)
            # for x in range(m):
            #     pre_inc[x + 1] = (pre_inc[x] + dp_inc[x]) % MOD
            #     pre_dec[x + 1] = (pre_dec[x] + dp_dec[x]) % MOD
            pre_dec = list(accumulate(dp_dec, initial = 0))
            pre_inc = list(accumulate(dp_inc, initial = 0))
            for x in range(m):
                dp_inc[x] = pre_dec[x] % MOD
                dp_dec[x] = (pre_inc[m] - pre_inc[x + 1]) % MOD
        return (sum(dp_inc) + sum(dp_dec)) % MOD
        '''
        
