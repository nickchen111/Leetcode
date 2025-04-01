# TC:O(nlgn + n * k * k) SC:O(n * k) 可以不排序
class Solution:
    def longestStrChain(self, words: List[str]) -> int:
        '''
        n^2 * k 大致上才能通過 問說最長長度
        '''
        n = len(words)
        f = defaultdict(int)
        words.sort(key=lambda x: len(x))
        @cache
        def dfs(i:int) -> int:
            m =len(words[i])
            ans = 1
            for j in range(m):
                s = words[i][:j] + words[i][j+1:]
                if s in f:
                    ans = max(ans, 1 + dfs(f[s]))
            f[words[i]] = i
            return ans
        return max(dfs(i) for i in range(n))
        '''
        for word in words:
            f[word] = 1
            m = len(word)
            for i in range(m):
                s = word[:i] + word[i+1:]
                if s in f and f[s] + 1 > f[word]:
                    f[word] = f[s] + 1
            if f[word] > ans:
                ans = f[word]
        return ans
        '''
