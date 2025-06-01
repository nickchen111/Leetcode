# 枚舉: TC:O(min(limit, n)) SC:O(1) 容斥: TC:O(1) SC:O(1)
def c2(n:int) -> int:
    return n * (n - 1) // 2 if n > 1 else 0
class Solution:
    def distributeCandies(self, n: int, limit: int) -> int:
        '''
        有多少方法可以分配糖果給三個小孩 讓每個小孩都不超過limit個數量
        1. O(n) 枚舉第一個人的狀況
        2. O(1) 放球問題
        合法方案數( <= limit) = 總方案數 - 不合法方案數(至少一個 > limit)
        總方案數: 有n個小球要放到3個有區別的盒子裡，允許空盒的方案數
        有n + 2個位置，因為就假設有兩個隔板n個球做組合 就會是放到3個盒子的狀況 -> C(n + 2, 2)
        集合A: 甲分到的糖果數 > limit 方案數(乙丙不關心) -> C(n - (limit+1) + 2, 2)
        集合B: 乙分到的糖果數 > limit 方案數(甲丙不關心) -> C(n - (limit+1) + 2, 2)
        集合B: 丙分到的糖果數 > limit 方案數(甲乙不關心) -> C(n - (limit+1) + 2, 2)

        集合A B : 甲乙分到的都超過limit -> C(n - 2 * (limit + 1) + 2, 2)
        ...
        集合A B C: C(n - 3 * (limit + 1) + 2, 2)
        '''
        return c2(n + 2) - 3 * c2(n - (limit + 1) + 2) + 3 * c2(n - 2 * (limit + 1) + 2) - c2(n - 3 * (limit + 1) + 2)
        '''
        O(n) 枚舉第一個人的狀況
        ans = 0
        # 去枚舉第一個人狀況 接下來就判斷第二個人的最大跟最小可以拿多少即可
        for i in range(min(limit, n) + 1):
            if n - i > 2 * limit: continue
            ans += min(limit, n - i) - max(0, n - i - limit) + 1
        return ans
        '''
