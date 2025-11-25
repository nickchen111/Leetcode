class Solution:
    def smallestRepunitDivByK(self, k: int) -> int:
        st = set()
        cur = 1
        ans = 1
        while cur % k not in st:
            if cur % k == 0:
                return ans
            ans += 1
            st.add(cur)
            cur = (cur * 10 + 1) % k
        return -1