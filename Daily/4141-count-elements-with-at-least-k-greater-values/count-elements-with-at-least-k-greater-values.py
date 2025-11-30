class Solution:
    def countElements(self, nums: List[int], k: int) -> int:
        n = len(nums)
        mp = Counter(nums)
        arr = list(set(nums))
        arr.sort()
        cnt = ans = 0
        for i in range(len(arr) - 1, -1, -1):
            if cnt >= k:
                ans += mp[arr[i]]
                continue
            cnt += mp[arr[i]]
        return ans
