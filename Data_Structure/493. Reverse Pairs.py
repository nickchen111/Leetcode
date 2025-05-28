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
    def reversePairs(self, nums) -> int:
        '''
        逆序對問題：找出所有 i < j 且 nums[i] > 2 * nums[j] 的配對數量
        從右到左遍歷，利用樹狀數組統計已處理元素中滿足條件的數量
        '''
        n = len(nums)
        ans = 0
        def divideAndConquer(l:int, r:int) -> List[int]:
            nonlocal ans
            if l == r:
                return [nums[l]]
            mid = (l + r) // 2
            left = divideAndConquer(l, mid)
            right = divideAndConquer(mid + 1, r)
            i = j = 0
            while i < len(left):
                while j < len(right) and left[i] > 2 * right[j]:
                    j += 1
                ans += j
                i += 1
            # merge
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
        divideAndConquer(0, n - 1)
        return ans
        

        '''
        樹狀數組
        arr = sorted(set(nums))
        ans = 0
        bit = FenwickTree(len(arr))
        for i in range(n - 1, -1, -1):
            target = (nums[i] + 1) // 2  # 等同於 ceil(nums[i] / 2) - 1
            j = bisect_left(arr, target)
            ans += bit.pre(j)
            idx = bisect_left(arr, nums[i]) + 1
            bit.update(idx, 1)
        return ans
        '''
