class Solution:
    def findDifferentBinaryString(self, nums: List[str]) -> str:
        st = {int(s,2) for s in nums}
        ans = 0
        while ans in st:
            ans += 1

        n = len(nums)
        return f"{ans:0{n}b}"