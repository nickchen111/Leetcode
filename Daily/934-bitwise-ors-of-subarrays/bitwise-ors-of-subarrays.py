class Solution:
    def subarrayBitwiseORs(self, nums: List[int]) -> int:
        n = len(nums)
        st = set()
        for i in range(n):
            st.add(nums[i])
            for j in range(i - 1, -1, -1):
                if nums[j] | nums[i] == nums[j]:
                    break
                nums[j] |= nums[i]
                st.add(nums[j])
        return len(st)
            