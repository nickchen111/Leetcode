# TC:O(n * 26 * (26 + lgk)) SC:O(n + 26)
class Solution:
    def smallestPalindrome(self, s: str, k: int) -> str:
        '''
        改問說第k小的回文串
        k <= 1e6 這題應該就是要跑一個 類似LC. 1415的構造
        利用回文串的特性 只需要構造一半即可
        此題還有個難點，就是枚舉每個字母的時候會發現排列方法太多了，而這題又不允許取模
        在這個狀況下如果是python 可以直接做但是其他語言要自己寫一個數學小技巧去規避溢出
        首先去枚舉填每個字母的狀況, 判斷一下是否從他開始的字母組成可以超過k，如果可以代表該位置就是填這個字母
        如果太小了，就把k扣掉該項字母，然後去枚舉另一個字母 不斷循環 直到k = 0 也剛好會填到最後一項位置
        '''
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


        
