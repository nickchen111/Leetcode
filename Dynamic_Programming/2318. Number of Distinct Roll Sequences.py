# TC:O(6*6*6*n) SC:O(n*6*6) 空間可以優化到 6 * n 但是偏難想
'''
MOD = 10 ** 9 + 7
@cache
def dfs(i:int, prev1:int, prev2:int) -> int:
    if i == 0:
        return 1
    ans = 0
    for j in range(1, 7):
        if j == prev2 or j == prev1 or gcd(j, prev1) != 1: continue
        ans = (ans + dfs(i - 1, j, prev1)) % MOD
    return ans
'''
class Solution:
    def distinctSequences(self, n: int) -> int:
        '''
        問說有多少種可能
        1. 每次擲骰子相鄰兩個GCD要是1 
        2. 相同元素需要間隔至少3 ex: 0 1 2 3
        n = 1e4
        看來需要上一個的狀態 以及前前一個前前前一個是啥
        1e4 * 6 * 6 * 6  * lga ~= 1e6 
        '''

        # 遞推 也可以放在全域 
        MOD = 10 ** 9 + 7
        if n == 1:
            return 6
        f = [[[0] * 6 for _ in range(6)] for _ in range(n + 1)]
        f[2] = [[int(j != i and gcd(j + 1, i + 1) == 1) for j in range(6)] for i in range(6)]
        for i in range(2, n):
            for j in range(6): # cur
                for last1 in range(6): # prev1
                    if last1 != j and gcd(last1 + 1, j + 1) == 1:
                        f[i + 1][j][last1] = (f[i + 1][j][last1] + sum(f[i][last1][last2] for last2 in range(6) if j != last2))% MOD
        return sum(sum(row) for row in f[n]) % MOD


        '''
        遞歸 寫在全域最快 
        return dfs(n, 7, 7)
        '''
