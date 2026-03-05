class Solution:
    def minOperations(self, s: str) -> int:
        s = list(map(int, s))
        def count(target:int) -> int:
            ans = 0
            for i, x in enumerate(s):
                if x & 1 != target ^ (i % 2):
                    ans += 1
            return ans
        return min(count(0), count(1))
