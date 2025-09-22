class Solution:
    def maxFrequencyElements(self, nums: List[int]) -> int:
        n = len(nums)
        mxf, ans = 0, 0
        mp = Counter(nums)
        for x,f in mp.items():
            if f == mxf:
                ans += f
            elif f > mxf:
                mxf = f
                ans = f
        return ans