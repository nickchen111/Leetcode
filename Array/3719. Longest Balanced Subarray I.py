# 暴力寫法 3720 為數據結構題單 TC:O(n) SC:O(n)
class Solution:
    def longestBalanced(self, nums: List[int]) -> int:
        n = len(nums)
        ans = 0
        for i in range(n):
            st = set()
            cnt_odd = 1 if nums[i] % 2 else 0
            cnt_even = 1 if nums[i] % 2 == 0 else 0
            st.add(nums[i])
            for j in range(i + 1, n):
                if nums[j] not in st:
                    cnt_odd += 1 if nums[j] % 2 else 0
                    cnt_even += 1 if nums[j] % 2 == 0 else 0
                    st.add(nums[j])
                if cnt_odd == cnt_even:
                    ans = max(ans, j - i + 1)
        return ans
                
