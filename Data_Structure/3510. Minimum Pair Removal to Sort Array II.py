# TC:O(nlgn) SC:O(n)
class UnionFind:
    def __init__(self, n):
        self.roots = [x for x in range(n)]

    def find(self, x):
        if self.roots[x] != x:
            self.roots[x] = self.find(self.roots[x])
        return self.roots[x]

    def union_to(self, x, y):
        self.roots[x] = y
        return

class Solution:
    def minimumPairRemoval(self, nums: List[int]) -> int:
        size = len(nums)
        sum_sl = SortedList()
        right = UnionFind(size + 2)
        left = UnionFind(size + 2)

        count = 0
        for i in range(size - 1):
            sum_sl.add((nums[i] + nums[i + 1], i))
            if nums[i] > nums[i + 1]:
                count += 1

        ans = 0
        while count:
            v, x = sum_sl[0]
            y = right.find(x + 2) - 1
            ans += 1

            l = left.find(x) - 1
            if l >= 0:
                sum_sl.remove((nums[l] + nums[x], l))
                sum_sl.add((nums[l] + v, l))
                if nums[l] > nums[x]:
                    count -= 1
                if nums[l] > v:
                    count += 1

            r = right.find(y + 2) - 1
            if r < size:
                sum_sl.remove((nums[y] + nums[r], y))
                sum_sl.add((v + nums[r], x))
                if nums[y] > nums[r]:
                    count -= 1
                if v > nums[r]:
                    count += 1

            if nums[x] > nums[y]:
                count -= 1

            sum_sl.remove((v, x))
            left.union_to(y + 1, x + 1)
            right.union_to(y + 1, r + 1)
            nums[x] = v
        return ans

        '''
        SortedList作法
        n = len(nums)
        sl = SortedList() 
        idx = SortedList(range(n)) 
        desc = 0

        for i, (x, y) in enumerate(pairwise(nums)):
            if x > y:
                desc += 1
            sl.add((x + y, i, i + 1))
        ans = 0
        while desc:
            v, x, y = sl[0]
            ans += 1
            x_idx = idx.bisect_left(x)
            # print(x_idx, x)
            if x_idx - 1 >= 0:
                l = idx[x_idx - 1]
                sl.remove((nums[l] + nums[x], l, x))
                sl.add((nums[l] + v, l, x))
                if nums[l] > nums[x] and v >= nums[l]:
                    desc -= 1
                elif nums[l] <= nums[x] and v < nums[l]:
                    desc += 1
            y_idx = idx.bisect_left(y)
            if y_idx + 1 < len(idx):
                r = idx[y_idx + 1]
                sl.remove((nums[y] + nums[r], y, r))
                sl.add((nums[r] + v, x, r))
                if nums[y] <= nums[r] and v > nums[r]:
                    desc += 1
                elif nums[y] > nums[r] and v <= nums[r]:
                    desc -= 1
            if nums[x] > nums[y]:
                desc -= 1
            sl.remove((v, x, y))
            idx.remove(y)
            nums[x] = v
        return ans
        '''
