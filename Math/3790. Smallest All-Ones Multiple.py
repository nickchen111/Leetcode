# TC:O(k) SC:O(k)
class Solution:
    def minAllOneMultiple(self, k: int) -> int:
        if k % 2 == 0 or k % 5 == 0:
            return -1
        st = set()
        n = 1
        while n and n not in st:
            st.add(n)
            n = (n * 10 + 1) % k
        return -1 if n else len(st) + 1
