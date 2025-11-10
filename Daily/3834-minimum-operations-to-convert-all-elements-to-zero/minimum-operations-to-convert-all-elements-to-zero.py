class Solution:
    def minOperations(self, nums):
        n = len(nums)
        pos = defaultdict(list)
        for i, x in enumerate(nums):
            pos[x].append(i)

        sl = SortedList([-1, n])  # 哨兵邊界
        ans = 0

        for key in sorted(pos.keys()):
            if key == 0:
                for i in pos[key]:
                    sl.add(i)
                continue

            indices = pos[key]
            tot = 1
            for j in range(1, len(indices)):
                l = sl.bisect_right(indices[j - 1])
                r = sl.bisect_left(indices[j])
                if r > l:
                    tot += 1
            ans += tot

            for i in indices:
                sl.add(i)

        return ans
