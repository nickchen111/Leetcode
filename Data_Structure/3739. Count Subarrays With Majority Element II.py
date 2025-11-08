# TC:O(nlogn) SC:O(1)
class Solution:
    def countMajoritySubarrays(self, nums: List[int], target: int) -> int:
        n = len(nums)
        arr = []
        for x in nums:
            arr.append(1 if x == target else -1)
        # 前綴和去解
        sl = SortedList()
        sl.add(0)
        ans = pre = 0
        for i in range(n):
            pre += arr[i]
            # 找比目前數字還小的數字有多少個
            ans += bisect_left(sl, pre)
            sl.add(pre)
        return ans
            
