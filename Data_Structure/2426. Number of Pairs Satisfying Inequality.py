# TC:O(nlgn) SC:O(n)
class FenwickTree:
    def __init__(self, n: int):
        self.tree = [0] * (n + 1) 
    def update(self, i: int, val: int) -> None:
        while i < len(self.tree):
            self.tree[i] += val
            i += i & -i
    def pre(self, i: int) -> int:
        res = 0
        while i > 0:
            res += self.tree[i]
            i &= i - 1
        return res
    def query(self, l: int, r: int) -> int:
        if r < l:
            return 0
        return self.pre(r) - self.pre(l - 1)
class Solution:
    def numberOfPairs(self, nums1: List[int], nums2: List[int], diff: int) -> int:
        '''
        找出有多少對 nums1[i] - nums1[j] <= nums2[i] - nums2[j] + diff
        看起來就是需要分類一下
        nums1[i] - nums2[i] <= nums1[j] - nums2[j] + diff
        -> nums[i] <= nums[j] + diff
        可以創建一個nums1[i] - nums2[u] 的 array
        正向枚舉的話當下的數值就當作是j 並且需要加上diff 
        這可以用樹狀數組維護 或者因為是逆序對的概念也可以用歸併排序merge sort
        python 還可以SortedList
        '''
        n = len(nums1)
        nums = [nums1[i] - nums2[i] for i in range(n)]
        ans = 0
        # SortedList
        sl = SortedList()
        for i in range(n):
            ans += sl.bisect_right(nums[i] + diff)
            sl.add(nums[i])
        return ans
        '''
        merge sort
        def merge_sort(l:int, r:int) -> List[int]:
            if l == r:
                return [nums[l]]
            nonlocal ans
            mid = (l + r) // 2
            left = merge_sort(l, mid)
            right = merge_sort(mid + 1, r)
            i = j = 0
            while i < len(left):
                while j < len(right) and left[i] > right[j] + diff:
                    j += 1
                ans += len(right) - j
                i += 1
            i = j = 0
            merged = []
            while i < len(left) and j < len(right):
                if left[i] <= right[j]:
                    merged.append(left[i])
                    i += 1
                else:
                    merged.append(right[j])
                    j += 1
            merged.extend(left[i:])
            merged.extend(right[j:])
            return merged
        merge_sort(0, n - 1)
        return ans
        '''
        '''
        樹狀數組
        arr = sorted(set(nums))
        bit = FenwickTree(len(arr))
        ans = 0
        for i in range(n):
            cur_num = nums[i] + diff
            ans += bit.pre(bisect_right(arr, cur_num))
            bit.update(bisect_left(arr, nums[i]) + 1, 1)
        return ans
        '''
