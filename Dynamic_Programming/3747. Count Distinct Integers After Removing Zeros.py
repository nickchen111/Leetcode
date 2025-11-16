# TC:O(logn) SC:O(logn)
class Solution:
    def countDistinct(self, n: int) -> int:
        s = str(n)
        L = len(s)


        # 數學解
        ans = 0
        # power9 = 1
        # for i in range(1, L):
        #     power9 *= 9
        #     ans += power9
        ans += (9 ** L - 9) // 8 # 錯位相減法

        for i, ch in enumerate(s):
            d = ord(ch) - ord('0')
            if d > 0:
                less = d - 1
                rem = L - i - 1
                ans += less * (9 ** rem)
            if d == 0:
                return ans
        return ans + 1
        '''
        數位DP
        @cache
        def dfs(i:int, is_num:bool, is_limit:bool) -> int:
            if i == L:
                return int(is_num)
            limit = int(s[i]) if is_limit else 9
            ans = 0
            if not is_num:
                ans += dfs(i + 1, False, False)
            for d in range(1, limit + 1):
                ans += dfs(i + 1, True, is_limit and (d == limit))
            return ans
        return dfs(0, False, True)
        '''
