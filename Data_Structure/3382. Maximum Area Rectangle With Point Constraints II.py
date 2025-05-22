# TC:O(nlgn) SC:O(n)
class FenwickTree:
    def __init__(self, n: int):
        self.tree = [0] * (n + 1) 
    def update(self, i: int, val: int) -> None:
        while i < len(self.tree):
            self.tree[i] += val
            i += i & -i
    def pre(self, i: int) -> int:
        res = 0
        while i > 0:
            res += self.tree[i]
            i &= i - 1
        return res
    def query(self, l: int, r: int) -> int:
        if r < l:
            return 0
        return self.pre(r) - self.pre(l - 1)
class Solution:
    def maxRectangleArea(self, xCoord: List[int], yCoord: List[int]) -> int:
        '''
        離線版本的二維數點問題，要在線的話應該是要用K-D tree
        計算[x1, x2] [y1,y2] 矩形區域內有多少個點
        本題只有詢問，沒有更新的二維數點問題
        剛才說的矩形，我們至藉由map保證邊界上沒有點，區域內不知道
        離線算法:
        將詢問拆分成兩個（前綴和的思想）
        計算 <= x1 - 1 和 y 屬於 [y1,y2]的點數量
        計算 <= x2 和 y 屬於 [y1,y2]的點數量
        按照x去把這2q個拆開後的詢問分組，從小到大遍歷x一邊更新樹狀數組，一邊回答詢問
        '''
        # 先去找出左邊與下面每個點會對到哪個點
        x_map = defaultdict(list)
        y_map = defaultdict(list)
        for x, y in zip(xCoord, yCoord):
            x_map[x].append(y)
            y_map[y].append(x)

        below = {}
        for x, ys in x_map.items():
            ys.sort()
            for y1, y2 in pairwise(ys):
                below[(x, y2)] = y1
        left = {}
        for y, xs in y_map.items():
            xs.sort()
            for x1, x2 in pairwise(xs):
                left[(x2, y)] = x1
        # 離散化用
        xs = sorted(x_map)
        ys = sorted(y_map) # 會自動取key
        queries = []
        # 列出右上角的點
        for x2, list_y in x_map.items():
            for y1, y2 in pairwise(list_y):
                x1 = left.get((x2,y2), None)
                if x1 is not None and left.get((x2, y1), None) == x1 and below.get((x1, y2), None) == y1:
                    queries.append((
                        bisect_left(xs, x1),
                        bisect_left(xs, x2),
                        bisect_left(ys, y1),
                        bisect_left(ys, y2),
                        (x2 - x1) * (y2 - y1)
                    ))
        # 將整理出來的離散化查詢 按照x1-1, x2 分組整理 內容記錄 需要
        grouped_queries = [[] for _ in range(len(xs))]
        for i, (x1, x2, y1, y2, _) in enumerate(queries):
            if x1 > 0:
                grouped_queries[x1 - 1].append((i, -1, y1, y2))
            grouped_queries[x2].append((i, 1, y1, y2))
        res = [0] * len(queries) # 回答詢問 每一個index 都代表一個右上角左下角湊出區域是否為合法矩形
        tree = FenwickTree(len(ys))
        for x, qs in zip(xs, grouped_queries):
            # x 從小到大 將當前x上的y都加入
            for y in x_map[x]:
                tree.update(bisect_left(ys, y) + 1, 1) # 將這些y 都新增進去樹狀數組
            # 開始判斷每個res離線查詢對應的index 點的增減
            for qid, sign, y1, y2 in qs:
                res[qid] += sign * tree.query(y1 + 1, y2 + 1)
            
        ans = -1
        for cnt, q in zip(res, queries):
            if cnt == 4:
                ans = max(ans, q[4])
        return ans
