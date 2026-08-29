class Solution:
    def lexicographicallySmallestArray(self, nums: List[int], limit: int) -> List[int]:
        n = len(nums)
        arr = sorted(zip(nums, range(n)))
        ans = [0] * n
        i = 0
        while i < n:
            st = i
            i += 1
            while i < n and arr[i][0] - arr[i-1][0] <= limit:
                i += 1
            idx = sorted(i for _,i in arr[st:i])
            for j,(x,_) in zip(idx, arr[st:i]):
                ans[j] = x
        return ans