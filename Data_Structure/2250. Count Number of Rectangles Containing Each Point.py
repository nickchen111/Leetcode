# TC:O(m + (n + h) * lgh + nlgn ) SC:O(n)
class Solution:
    def countRectangles(self, rectangles: List[List[int]], points: List[List[int]]) -> List[int]:
        '''
        狗py 用SortedList做
        '''
        n, m = len(rectangles), len(points)
        rectangles.sort(key=lambda x: x[0])
        points_idx = [[points[i][0], points[i][1], i] for i in range(m)]
        points_idx.sort()
        p1, p2 = 0, 0
        sl = SortedList(rectangles[i][1] for i in range(n)) # 將高度通通加入
        ans = [0] * m
        while p1 < m:
            # 將目前寬度比我低的刪掉
            pl, ph, idx = points_idx[p1]
            while p2 < n and rectangles[p2][0] < pl:
                sl.remove(rectangles[p2][1])
                p2 += 1
            ans[idx] = len(sl) - bisect_left(sl, ph)
            p1 += 1
        return ans
            
        
