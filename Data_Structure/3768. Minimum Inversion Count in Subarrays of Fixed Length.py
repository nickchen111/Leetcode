# TC:O(nlogn) SC:O(n)
class Solution:
    def minInversionCount(self, nums, k):
        n = len(nums)
        sl = SortedList()
        i = 0
        cnt = 0
        ans = inf

        for j in range(n):
            cnt += len(sl) - sl.bisect_right(nums[j])
            sl.add(nums[j])

            if j - i + 1 == k:
                ans = min(ans, cnt)

                smaller = sl.bisect_left(nums[i])
                cnt -= smaller

                sl.remove(nums[i])
                i += 1

        return ans

  class FenwickTree:
    def __init__(self, n: int):
        self.tree = [0] * (n + 1)


    def update(self, i: int, val: int) -> None:
        t = self.tree
        while i < len(t):
            t[i] += val
            i += i & -i

    def pre(self, i: int) -> int:
        t = self.tree
        res = 0
        while i > 0:
            res += t[i]
            i &= i - 1
        return res


class Solution:
    def minInversionCount(self, nums: List[int], k: int) -> int:
        sorted_nums = sorted(set(nums))
        mp = {x: i for i, x in enumerate(sorted_nums, 1)}
        for i, x in enumerate(nums):
            nums[i] = mp[x]

        t = FenwickTree(len(sorted_nums))
        inv = 0
        ans = inf

        for i, x in enumerate(nums):
            t.update(x, 1)
            inv += min(i + 1, k) - t.pre(x)

            left = i + 1 - k
            if left < 0:
                continue

            # 2. 更新答案
            ans = min(ans, inv)
            if ans == 0:
                break

            # 3. 出
            out = nums[left]
            inv -= t.pre(out - 1)
            t.update(out, -1)

        return ans
