class Solution:
    def prefixesDivBy5(self, nums: List[int]) -> List[bool]:
        cur = 0
        ans = []
        for x in nums:
            cur = (cur * 2 + x) % 5
            ans.append(True if cur % 5 == 0 else False)
        return ans
