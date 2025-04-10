# TC:O(n * 10 * 2 * 2) n 最多50 from 2^n = 10 ^ 15 SC:O(n * 2 * 2)
class Solution:
    def numberOfPowerfulInt(self, start: int, finish: int, limit: int, s: str) -> int:
        '''
        就是數位DP
        '''
        l = len(s)
        s_mod = pow(10, l)
        s = int(s)
        #目前走到哪, 是否是數字，是否貼著下界, 程式中需要判斷剩下的字串是否要填上s了
        def countPowerful(num:int) -> int:
            s1 = list(map(int, str(num)))
            n = len(s1)
            if l > n or (l == n and num < s): return 0
            @cache
            def dfs(i:int, is_num:bool, is_limit:bool) -> int:
                if i == n - l:
                    return 1 if not is_limit or num % s_mod >= s else 0
                ans = 0
                if not is_num:
                    ans = dfs(i+1, False, False) #  不選
                up = limit if not is_limit else min(limit, s1[i]) #最大值
                down = 1 if not is_num else 0
                for j in range(down, up + 1):
                    ans += dfs(i+1, True, is_limit and j == s1[i])
                return ans
            dfs.cache_clear()
            return dfs(0, False, True)
        return countPowerful(finish) - countPowerful(start - 1)


                
