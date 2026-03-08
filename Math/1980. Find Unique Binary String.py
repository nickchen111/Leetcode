# TC:O(n) SC:O(1)
class Solution:
    def findDifferentBinaryString(self, nums: List[str]) -> str:
        # cantor 對角線
        ans = [''] * len(nums)
        for i, s in enumerate(nums):
            ans[i] = '1' if s[i] == '0' else '0'
        return "".join(ans)

        #暴力枚舉
        st = {int(s,2) for s in nums}
        ans = 0
        while ans in st:
            ans += 1

        n = len(nums)
        return f"{ans:0{n}b}"
