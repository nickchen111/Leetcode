class Solution:
    def maxDistinct(self, s: str) -> int:
        st = set()
        for ch in s:
            if ch not in st:
                st.add(ch)
        return len(st)