# TC:O(n) SC:O(n)
class Solution:
    def removeSubstring(self, s: str, k: int) -> str:
        st = []
        for b in s:
            if st and st[-1][0] == b:
                st[-1][1] += 1
            else:
                st.append([b, 1])
            if b == ')' and len(st) > 1 and st[-2][1] >= k and st[-1][1] == k:
                st.pop()
                st[-1][1] -= k
                if st[-1][1] == 0:
                    st.pop()
        return ''.join(b * cnt for b, cnt in st)
