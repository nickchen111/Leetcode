class Solution:
    def minimumPairRemoval(self, nums: List[int]) -> int:
        '''
        用sl可以快速找出要修改的位置 修掉以後就看左右兩點是否要修改
        先直接刪除再判斷僅存兩點是否要加回去
        '''
        n = len(nums)
        sl = SortedList()
        idx = SortedList(range(n))
        desc = ans = 0
        for i, (x, y) in enumerate(pairwise(nums)):
            if x > y:
                desc += 1
            sl.add((x + y, i, i + 1))
        while desc:
            v, x, y = sl[0]
            ans += 1
            # 將左右邊點移除
            x_idx = idx.bisect_left(x)
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
                sl.add((v + nums[r], x, r))
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

        
