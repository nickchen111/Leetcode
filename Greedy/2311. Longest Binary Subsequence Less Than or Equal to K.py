class Solution:
    def longestSubsequence(self, s: str, k: int) -> int:
        '''
        問說最長的lcs 用十進制表示 <= k 是多少
        n = 1000
        可以枚舉選哪個 dp[i] 走到i以這為結尾的符合 <= k的最長長度是多少
        '''
        n = len(s)
        zeros = s.count('0')
        ones_positions = []
        for i in range(n):
            if s[i] == '1':
                ones_positions.append(i)
        
        val = 0
        ones_count = 0
        
        for pos in reversed(ones_positions):
            power = 1 << (n - 1 - pos)
            if val + power <= k:
                val += power
                ones_count += 1
            else:
                break
        
        return zeros + ones_count
