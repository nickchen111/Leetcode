class Solution:
    def minCost(self, basket1: List[int], basket2: List[int]) -> int:
        '''
        只要有其中一個數字出現odd次就不可能成功 剩餘就是問說最低成本去交換成一魔一樣的數組
        感覺很像貪心 先排序 然後思考該如何換比較好
        [2, 2, 2, 4]. [1, 1, 2, 4] 盡量拿少的去交換大的 這樣可以取最小 然後順便將多的給削掉
        要換的肯定會是odd? 不一定 所以需要判斷一下 
        做成這樣的資料結構 [num, cnt] cnt = abs(b1 - b2) // 2 需要替換的次數
        在按照大小排序即可 bug -> 卡在可以考慮最小的元素去交換兩次的狀況
        '''
        cnt = defaultdict(int)
        for x, y in zip(basket1, basket2):
            cnt[x] += 1
            cnt[y] -= 1

        a, b = [], []
        for x, c in cnt.items():
            if c % 2:
                return -1
            if c > 0:
                a.extend([x] * (c // 2))
            else:
                b.extend([x] * (-c // 2))

        a.sort()
        b.sort(reverse=True)
        mn = min(cnt)

        return sum(min(x, y, mn * 2) for x, y in zip(a, b))