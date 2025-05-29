# TC: O(nlgn) SC:O(n)
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
    def countRangeSum(self, nums: List[int], lower: int, upper: int) -> int:
        '''
        有哪些subarray相加起來在範圍之間
        目前這個數字當作左端點 找一段區間是  lower <= nums[i] + x <= upper
        lower <= presum[j] - presum[i] <= upper
        presum[j] - upper <= presum[i] <= presum[j] - lower
        '''
        sl = SortedList()
        prefix_sum = 0
        ans = 0
        sl.add(0)
        for num in nums:
            prefix_sum += num
            # 找有多少 prefix_sum[j] 落在 [prefix_sum - upper, prefix_sum - lower]
            left = sl.bisect_left(prefix_sum - upper)
            right = sl.bisect_right(prefix_sum - lower)
            ans += right - left
            sl.add(prefix_sum)
        
        return ans
        '''
        歸併排序
        presum = [0]
        tot = 0
        for x in nums:
            tot += x
            presum.append(tot)
        ans = 0
        def divide_merge(l:int, r:int) -> List[int]:
            if l == r:
                return [presum[l]]
            nonlocal ans
            mid = (l + r) // 2
            left = divide_merge(l, mid)
            right = divide_merge(mid + 1, r)
            # 計算數量 
            j = k = 0
            for i in range(len(left)):
                while k < len(right) and right[k] - left[i] <= upper:
                    k += 1
                while j < len(right) and right[j] - left[i] < lower:
                    j += 1
                ans += k - j
            merged = []
            i = j = 0
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
        divide_merge(0, len(presum) - 1)
        return ans
        '''
        '''
        樹狀數組
        arr = []
        for x in presum:
            arr.append(x)
            arr.append(x - lower)
            arr.append(x - upper)
        arr = sorted(set(arr))
        bit = FenwickTree(len(arr))
        ans = 0
        for i in range(len(presum)):
            l, r = bisect_left(arr, presum[i] - upper) + 1, bisect_right(arr, presum[i] - lower)
            ans += bit.query(l, r)
            bit.update(bisect_left(arr, presum[i]) + 1, 1)
        return ans
        '''
