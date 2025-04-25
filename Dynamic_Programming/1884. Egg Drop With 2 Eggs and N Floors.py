# DP: TC:O(n^2) SC:O(n) Math: TC:O(1) SC:O(1)
f = [0] * 1001
for i in range(1, len(f)):
    f[i] = min(max(j, f[i - j] + 1) for j in range(1, i + 1))

class Solution:
    def twoEggDrop(self, n: int) -> int:
        '''
        數學解, 從假設你只有5次機會開始丟, n = 15 你起初就只能從 5樓開始，因為如果5樓破了 你還可以從1嘗試到4
        再從 5 + 4 = 9樓 開始以此類推... 所以令最少需要X次 x + (x - 1) + (x -2) + ... + 1 >= n
        x * (x + 1) // 2 >= n 
        '''
        return ceil((sqrt(n * 8 + 1) - 1) / 2)
        '''
        遞歸
        return f[n]
        '''
        '''
        遞歸
        @cache
        def dfs(i:int) ->int:
            if i == 0:
                return 0
            ans = i
            for j in range(1, i+1):
                ans = min(ans, max(j, dfs(i - j) + 1))
            return ans
        return dfs(n)
        '''
