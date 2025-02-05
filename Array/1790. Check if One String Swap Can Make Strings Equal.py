# TC:O(n) SC:O(1)
class Solution:
    def areAlmostEqual(self, s1: str, s2: str) -> bool:
        mp1 = Counter(s1)
        mp2 = Counter(s2)
        if mp1 != mp2:
            return False
        cnt = 0
        for i in range(len(s1)):
            cnt += s1[i] != s2[i]
        return cnt <= 2
