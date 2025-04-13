# TC:O(lgn + n * 2 * 2 * 10) n = 100 SC:O(n * 2 * 2 * 10 + lgn)
class Solution:
    def countNumbers(self, l: str, r: str, b: int) -> int:
        MOD = 10 ** 9 + 7
        def convert_to_base8(decimal_str,):
            if decimal_str == "0":
                return "0"
            num = [int(c) for c in decimal_str]

            octal_result = ""

            # 不斷地除以b，直到商為0
            while num and not (len(num) == 1 and num[0] == 0):
                remainder = 0
                new_num = []
                leading_zero = True

                for digit in num:
                    current = remainder * 10 + digit
                    if current // b != 0 or not leading_zero or len(new_num) > 0:
                        new_num.append(current // b)
                        leading_zero = False
                    remainder = current % b

                # 添加這一次的餘數到結果開頭
                octal_result = str(remainder) + octal_result
                num = new_num

            return octal_result
        def check(s:str) -> int:
            m = len(s)
            flag = True
            for i in range(m-1):
                if s[i] > s[i+1]:
                    flag = False
                    break
            return 1 if flag else 0
        l_b = convert_to_base8(l)
        r_b = convert_to_base8(r)
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
