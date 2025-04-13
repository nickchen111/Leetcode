# TC:O(lgn + n * 2 * 2 * 10 * U) U 為前一個數字~10的長度 n = 100 SC:O(n * 2 * 2 * 10 + lgn)
class Solution:
    def countNumbers(self, l: str, r: str, b: int) -> int:
        MOD = 10 ** 9 + 7
        def trans(s: str) -> List[int]:
            x = int(s)
            digits = []
            while x:
                x, r = divmod(x, b)
                digits.append(r)
            digits.reverse()
            return digits

        def check(s:str) -> int:
            m = len(s)
            flag = True
            for i in range(m-1):
                if s[i] > s[i+1]:
                    flag = False
                    break
            return 1 if flag else 0
        l_b = trans(l)
        r_b = trans(r)
        def countNUmber(s:str) -> int:
            n = len(s)
            @cache
            def dfs(i:int, is_num:bool, is_limit:bool, prev:int) -> int:
                if i == n:
                    return 1 if is_num else 0
                ans = 0
                if not is_num:
                    ans = dfs(i + 1, False, False, prev)
                down = prev if is_num else 1# 要比之前的大或者一樣 如果之前都還沒選過 可以從１開始
                up = int(s[i]) if is_limit else b - 1
                for j in range(down, up + 1):
                    ans = (ans + dfs(i + 1, True, is_limit and j == up, j)) % MOD
                return ans
            return dfs(0, False, True, 0) % MOD
        return (countNUmber(r_b) - countNUmber(l_b) + check(l_b) + MOD) % MOD
