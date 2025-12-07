class Solution:
    def sortByReflection(self, nums: List[int]) -> List[int]:
        n = len(nums)
        arr = []
        for i, x in enumerate(nums):
            tmp = []
            while x:
                x, d = divmod(x, 2)
                tmp.append(d)
            cur = 0
            for j in range(len(tmp)):
                cur = cur * 2 + tmp[j]
            # cur 代表目前數字
            arr.append((cur, i))
        arr.sort(key=lambda t: (t[0], nums[t[1]]))
        ans = []
        for i in range(n):
            ans.append(nums[arr[i][1]])
        return ans
