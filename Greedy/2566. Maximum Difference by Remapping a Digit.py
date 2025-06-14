# TC:O(n) SC:O(1) 
class Solution:
    def minMaxDifference(self, num: int) -> int:
        s = list(int(x) for x in (str(num)))
        targetMx = 9
        for x in s:
            if x != 9:
                targetMx = x
                break
        targetMn = s[0]
        mx, mn = 0, 0
        for i in range(len(s)):
            if s[i] == targetMx:
                mx = mx * 10 + 9
            else:
                mx = mx * 10 + s[i]
            if s[i] == targetMn:
                mn = mn * 10
            else:
                mn = mn * 10 + s[i]
        return mx - mn
