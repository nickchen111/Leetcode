class Solution:
    def minimumTime(self, d: List[int], r: List[int]) -> int:
        # 會考慮到 跨度, 所需派送包裹
        d1, d2 = d
        r1, r2 = r
        l = lcm(r1, r2)

        def check(t: int) -> bool:
            return d1 <= t - t // r1 and d2 <= t - t // r2 and d1 + d2 <= t - t // l

        left = d1 + d2 - 1
        right = (d1 + d2) * 2 - 1
        while left < right:
            mid = (left + right) // 2
            if check(mid):
                right = mid
            else:
                left = mid + 1
        return right
