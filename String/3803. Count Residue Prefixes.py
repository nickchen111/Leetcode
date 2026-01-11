# TC:O(n) SC:O(1)
class Solution:
    def residuePrefixes(self, s: str) -> int:
        ans = st = 0
        for i, ch in enumerate(s):
            st |= 1 << (ord(ch) - ord('a'))
            if st.bit_count() == (i + 1) % 3:
                ans += 1
            if st.bit_count() >= 3:
                break
        return ans
