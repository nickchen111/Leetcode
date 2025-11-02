class Solution:
    def findMissingElements(self, nums: List[int]) -> List[int]:
        mx, mn = max(nums), min(nums)
        st = set()
        for i in range(mn, mx + 1):
            st.add(i)
        for x in nums:
            st.remove(x)
        return sorted(list(st))