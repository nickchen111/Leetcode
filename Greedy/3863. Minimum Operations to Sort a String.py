# TC:O(n) SC:O(1)
class Solution:
    def minOperations(self, s: str) -> int:
        if all(x <= y for x, y in pairwise(s)):
            return 0
        if len(s) <= 2:
            return -1
        mn = min(s)
        mx = max(s)
        if s[0] == mn or s[-1] == mx:
            return 1
    
        if any(ch == mx or ch == mn for ch in s[1:-1]): # 從1 ~ n - 2 看是否有最大or最小 就可以一步走到上一個情況
            return 2
        return 3
