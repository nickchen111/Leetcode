# TC:O(n * m) m 為平均字串長度 SC:O(m)
class Solution:
    def countAndSay(self, n: int) -> str:
        # 遞推
        ans = ['1']
        for level in range(2, n + 1):
            tmp = []
            i = 0
            m = len(ans)
            while i < m:
                j = i
                while j < m and ans[j] == ans[i]:
                    j += 1
                cnt = j - i
                tmp.append(str(cnt))
                tmp.append(ans[i])
                i = j

            ans = tmp
        return ''.join(ans)

        '''
        def dfs(level: int, s: str) -> str:
            if level == n:
                return s
            ans = []
            i = 0
            m = len(s)
            while i < m:
                j = i
                while j < m and s[j] == s[i]:
                    j += 1
                cnt = j - i
                ans.append(str(cnt))
                ans.append(s[i])
                i = j

            next_s = ''.join(ans)
            return dfs(level + 1, next_s)
        return dfs(1, '1')
        '''
