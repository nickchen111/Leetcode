# TC:O(n) SC:O(n)
class Solution:
    def minOperations(self, nums: List[int]) -> int:
        n = len(nums)
        start = -1
        st = set()
        for i in range(n - 1, -1, -1):
            if nums[i] in st:
                start = i
                break
            st.add(nums[i])
        if start == -1:
            return 0
        num = start + 1
        return (num + 2) // 3
