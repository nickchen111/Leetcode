# TC:O(n^2) SC:O(n)
class Solution:
    def centeredSubarrays(self, nums: List[int]) -> int:
        ans = 0
        n = len(nums)
        for i in range(n):
            st = set()
            cur = 0
            for j in range(i, n):
                cur += nums[j]
                st.add(nums[j])
                if cur in st:
                    ans += 1
        return ans
