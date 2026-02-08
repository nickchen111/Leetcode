class Solution:
    def mergeAdjacent(self, nums: List[int]) -> List[int]:
        st = []
        for x in nums:
            cur = x
            while st and st[-1] == cur:
                cur = st[-1] + cur
                st.pop()
            st.append(cur)
        return st