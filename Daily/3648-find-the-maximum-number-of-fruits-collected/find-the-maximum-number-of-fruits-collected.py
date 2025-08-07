class Solution:
    def maxCollectedFruits(self, fruits: List[List[int]]) -> int:
        '''
        三個人走n-1步到右下角 可以採收最多多少水果
        左上角的只能獨佔斜對角線水果
        另外兩邊的就各自吃那個角落的水果最大值
        '''
        ans = 0
        n = len(fruits)
        for i in range(n):
            ans += fruits[i][i]
        @cache
        def dfs(i:int, j:int) -> int:
            if j >= n or j < n - 1 - i:
                return -inf
            if i == 0:
                return fruits[i][j]
            return max(dfs(i - 1, j - 1), dfs(i - 1, j + 1), dfs(i - 1, j)) + fruits[i][j]
        ans += dfs(n - 2, n - 1)
        dfs.cache_clear()
        for i in range(n):
            for j in range(n):
                fruits[i][j] = fruits[j][i]
        ans += dfs(n - 2, n - 1)
        return ans