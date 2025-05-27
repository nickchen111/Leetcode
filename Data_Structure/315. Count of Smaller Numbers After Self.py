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
    def countSmaller(self, nums: List[int]) -> List[int]:
        '''
        計算右邊有多少個比我小的數字 -> 逆序對
        1. 樹狀數組
        2. 歸併排序
        '''
        n = len(nums)
        ans = [0] * n
        arr = list(enumerate(nums))  # [(index, value)]

        def merge_sort(start, end):
            if start == end:
                return arr[start:end + 1]
            
            mid = (start + end) // 2
            left = merge_sort(start, mid)
            right = merge_sort(mid + 1, end)
            merged = []
            j = 0  # 右邊有多少個小於左邊的數
            i = 0
            while i < len(left):
                while j < len(right) and right[j][1] < left[i][1]:
                    j += 1
                ans[left[i][0]] += j
                i += 1

            # merge 排序部分
            l = r = 0
            while l < len(left) and r < len(right):
                if left[l][1] <= right[r][1]:
                    merged.append(left[l])
                    l += 1
                else:
                    merged.append(right[r])
                    r += 1
            merged.extend(left[l:])
            merged.extend(right[r:])
            return merged
        merge_sort(0, n - 1)
        return ans
            
            

        '''
        樹狀數組
        ans = [0] * n
        # 離散化
        arr = sorted(set(nums))
        bit = FenwickTree(len(arr))
        for i in range(n - 1, -1, -1):
            j = bisect_left(arr, nums[i])
            ans[i] = bit.pre(j)
            bit.update(j + 1, 1)
        return ans
        '''

