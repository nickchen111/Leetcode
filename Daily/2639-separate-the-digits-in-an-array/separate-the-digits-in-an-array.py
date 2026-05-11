class Solution:
    def separateDigits(self, nums: List[int]) -> List[int]:
        ans = []
        for x in nums:
            tmp = []
            while x:
                tmp.append(x % 10)
                x //= 10
            for i in range(len(tmp) - 1, -1, -1):
                ans.append(tmp[i])
        return ans
