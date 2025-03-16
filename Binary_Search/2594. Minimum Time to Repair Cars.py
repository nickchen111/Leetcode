# TC:O(n + M * lgm^c) M為max(ranks) m 為min(ranks) c 為 需要處理的車子數量 SC:O(M)
class Solution:
    def repairCars(self, ranks: List[int], cars: int) -> int:
        '''
        r 越小 代表工人修得越快 問說最少需要多少時間修車
        '''
        cnt = Counter(ranks)
        left, right = 0, min(ranks) * cars * cars
        def check(mid:int) -> bool:
            return True if sum(isqrt(mid // r) * c for r, c in cnt.items()) >= cars else False
        while left < right:
            mid = left + (right - left) // 2
            if check(mid):
                right = mid
            else: left = mid + 1
        return left
