class Solution:
    def minDeletionSize(self, strs: List[str]) -> int:
        '''
        每個都要變成sort 找LCS n = 100
        n -> n以內
        '''
        m, n = len(strs), len(strs[0])
        dp = [1] * n
        for i in range(n):
            for j in range(i):
                flag = True
                for k in range(m):
                    if strs[k][i] < strs[k][j]:
                        flag = False
                        break
                if flag:
                    dp[i] = max(dp[i], dp[j] + 1)
        return n - max(dp)
