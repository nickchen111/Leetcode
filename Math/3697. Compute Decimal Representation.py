# TC:O(logn) SC:O(1)
class Solution:
    def decimalRepresentation(self, n: int) -> List[int]:
        ans = []
        pow10 = 1
        while n:
            n,d = divmod(n, 10)
            if d:
                ans.append(d * pow10)
            pow10 *= 10
        return list(reversed(ans))
