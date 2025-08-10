class Solution:
    def reorderedPowerOf2(self, n: int) -> bool:
        n = list(str(n))
        n.sort()
        for i in range(32):
            cur = list(str(1 << i))
            cur.sort()
            if cur == n:
                return True
        return False
            