class Solution:
    def maxAverageRatio(self, classes: List[List[int]], extraStudents: int) -> float:
        '''
        想讓通過率 ex x + y + z // 3  最大該怎麼分配學生進去
        首先當然會想說讓通過率較低的害群之馬班級拉高 但是他拉高的比率要怎麼計算
        就讓拉高比率丟進去pq 去做
        '''

        pq = []
        n = len(classes)
        totalPass = 0.0
        for x, y in classes:
            totalPass += x / y
            inc_ratio = (x + 1) / (y + 1) - x / y
            heappush(pq, (-inc_ratio, x, y))
        while extraStudents:
            extraStudents -= 1
            ratio, x, y = heappop(pq)
            x += 1
            y += 1
            totalPass += -ratio
            heappush(pq, (-( (x + 1) / (y + 1) - x / y ), x, y))
        return totalPass / n
