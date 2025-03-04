# Math & DP -> TC:O(lgn) SC:O(1) & TC:O(n * m) m = 15, SC:O(n * m)
class Solution:
    def checkPowersOfThree(self, n: int) -> bool:
        while n > 0:
            if n % 3 == 1 or n % 3 == 0:
                n //= 3
            else: return False
        return True
        '''
        遞歸
        pow3 = [1]
        while pow3[-1] * 3 <= n:
            pow3.append(pow3[-1] * 3)
        m = len(pow3)
        @cache
        def dfs(i : int, j:int) -> bool:
            if i == 0:
                return True
            if j == m:
                return False
            ans = False
            for k in range(j,len(pow3)):
                if i - pow3[k] >= 0:
                    ans |= dfs(i - pow3[k], k+1)
                else: break
            return ans
        return dfs(n, 0)
        '''

# 集合預處理 TC:O(1)均攤 2^15 ~= 1 SC:O(2^m) m 為15
base, MX, dp = 1, 15, set([0])
while MX > 0:
    base, MX, dp = base * 3, MX-1, set(x + base for x in dp) | dp
class Solution:
    def checkPowersOfThree(self, n: int) -> bool:
        return n in dp
