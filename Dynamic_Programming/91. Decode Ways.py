# TC:O(n) SC:O(1)
class Solution:
    def numDecodings(self, s: str) -> int:
        '''
        就是0開頭的不能 其他的只要是1-26 就都有數字代表他
        f[i] = f[i-1] + f[i-2] if s[i] + s[i-1] in range(1,26)
        '''
        n = len(s)
        nums = list(map(lambda ch: ord(ch) - ord('0'), s))
        f0, f1 = 1, 1 if nums[0] != 0 else 0
        f2 = f1
        for i in range(1,n):
            if nums[i] != 0:
                f2 = f1
            else: f2 = 0
            if i and 10 <= nums[i] + nums[i-1] * 10 <= 26:
                f2 += f0
            f0, f1 = f1, f2
        return f2
        '''
        遞推
        f = [0] * (n+1)
        f[0] = 1
        for i in range(n):
            if nums[i] != 0:
                f[i+1] = f[i]
            if i and 10 <= nums[i] + nums[i-1] * 10 <= 26:
                f[i+1] += f[i-1]
        return f[n]
        '''
        '''
        遞歸
        @cache
        def dfs(i:int) -> int:
            if i == n:
                return 1
            if nums[i] == 0:
                return 0
            ans = dfs(i+1)
            if i + 1 < n:
                num = nums[i] * 10 + nums[i+1]
                if 10 <= num <= 26:
                    ans += dfs(i+2)
            return ans
        
        return dfs(0)
        '''
