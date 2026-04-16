class Solution:
    def solveQueries(self, nums: List[int], queries: List[int]) -> List[int]:
        indices = defaultdict(list)
        for i, x in enumerate(nums):
            indices[x].append(i)
        n = len(nums)
        for p in indices.values():
            i0 = p[0]
            p.insert(0, p[-1] - n) # python 用 0 表示插入位置
            p.append(i0 + n)
        for qi, i in enumerate(queries):
            p = indices[nums[i]]
            if len(p) == 3:
                queries[qi] = -1
            else:
                j = bisect_left(p, i)
                queries[qi] = min(i - p[j-1], p[j+1] - i)
        return queries