class Solution:
    def minNumberOfSeconds(self, mountainHeight: int, workerTimes: List[int]) -> int:
        h = [(t, t, t) for t in workerTimes]
        heapify(h)
        for _ in range(mountainHeight):
            tot, cur, base = h[0]
            heapreplace(h, (tot + cur + base, cur + base, base))
        return tot
