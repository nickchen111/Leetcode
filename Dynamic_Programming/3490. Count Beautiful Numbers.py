# TC:O(n^6 * D^2) SC:O(n^6 * D)
# s = {1}
# for k in range(9):
#     s = set(x * d for x in s for d in range(10))
#     print(k+1, len(s))
memo = {}
high = []
class Solution:
    def beautifulNumbers(self, l: int, r: int) -> int:
        '''
        這題盲點在於 要先判斷 9...9 9個9會有多少種相乘的結果 會發現其實沒想像中的多 大概3xxx多個
        '''
        # n = 0
        def dfs(i:int, m:int, s:int, is_limit:bool, is_num:bool) -> int:
            if i < 0:
                return 1 if s and m % s == 0 else 0
            t = (i, m, s)
            if is_num and not is_limit and t in memo: return memo[t]
            ret = 0 if is_num else dfs(i-1, m, s, False, False)
            up = high[i] if is_limit else 9
            for d in range(0 if is_num else 1, up+1):
                ret += dfs(i-1, m * d, s + d, is_limit and d == up, True)
            if not is_limit and is_num:
                memo[t] = ret
            return ret
        def calc(r:int):
            global high
            high = list(map(int, str(r)))[::-1]
            # global n
            # n = len(high)
            return dfs(len(high) - 1, 1, 0, True, False)
            
        return calc(r) - calc(l-1)
