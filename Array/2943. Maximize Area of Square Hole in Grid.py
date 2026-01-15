# TC:O(nlogn) SC:O(1)
class Solution:
    def maximizeSquareHoleArea(self, n: int, m: int, hBars: List[int], vBars: List[int]) -> int:
        def f(a: List[int]) -> int:
            a.sort()
            cnt = mx = 0
            for i in range(len(a)):
                if i and a[i] == a[i - 1] + 1:
                    cnt += 1
                else: 
                    cnt = 1
                mx = max(mx, cnt)
            return mx
        side = min(f(hBars), f(vBars)) + 1
        return side * side

