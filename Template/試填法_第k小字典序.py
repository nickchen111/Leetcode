# 主要應用於 構造第k小字典序的題目 此題有搭配組合數 LC.3518
class Solution:
    def smallestPalindrome(self, s: str, k: int) -> str:
        n = len(s)
        m = n // 2 # 只需要構造一半的字
        cnt = [0] * 26
        for ch in s[:m]:
            cnt[ord(ch) - ord('a')] += 1
        def comb(n:int, m:int) -> int:
            m = min(m, n - m) # 因為對稱性 cn取m 跟 cn取 n - m是一樣的
            res = 1
            for i in range(1, m + 1):
                res = res * (n + 1 - i) // i
                if res >= k:
                    return k
            return res

        def perm(sz:int): # 計算剩下這麼多空位 能夠組成的排列個數
            res = 1
            for c in cnt:
                if c == 0: continue
                res *= comb(sz, c) # 這裡大概lgk 而且不是每次都是lgk 而是 26 + lgk
                if res >= k:
                    return k
                sz -= c
            return res
        if perm(m) < k:
            return ""
        left_s = [''] * m
        for i in range(m):
            for j in range(26):
                if cnt[j] == 0: continue
                cnt[j] -= 1
                p = perm(m - i - 1)
                if p >= k:
                    left_s[i] = chr(ord('a') + j)
                    break
                k -= p
                cnt[j] += 1
        ans = ''.join(left_s)
        if n % 2:
            ans += s[n // 2]
        return ans + ''.join(reversed(left_s))


        
