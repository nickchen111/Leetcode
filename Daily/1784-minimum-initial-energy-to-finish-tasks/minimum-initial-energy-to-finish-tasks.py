class Solution:
    def minimumEffort(self, tasks: List[List[int]]) -> int:
        tasks.sort(key = lambda t: t[0] - t[1])
        ans = 0
        s = 0
        for actual, minimum in tasks:
            ans = max(ans, s + minimum)
            s += actual
        return ans