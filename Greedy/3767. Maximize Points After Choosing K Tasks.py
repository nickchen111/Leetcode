# TC:O(nlogn) SC:O(n)
class Solution:
    def maxPoints(self, t1: List[int], t2: List[int], k: int) -> int:
        '''
        至少k個任務用t1, 可以得到的最多分數為?
        可去計算兩個任務的差 t2 - t1 差越多代表用t2越好 越少就用t1越好
        '''
        n = len(t1)
        diff = [t2[i] - t1[i] for i in range(n)]
        pq = []
        for i, d in enumerate(diff):
            heappush(pq, [d, i])
        ans = 0
        while pq:
            d, i = heappop(pq)
            if k > 0:
                ans += t1[i]
                k -= 1
                continue
            if d > 0:
                ans += t2[i]
            else:
                ans += t1[i]
                k -= 1
        return ans
                
            
