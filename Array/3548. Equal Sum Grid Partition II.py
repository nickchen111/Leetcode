# TC:O(m * n) SC:O(m * n)
class Solution:
    def canPartitionGrid(self, grid: List[List[int]]) -> bool:
        total = sum(sum(row) for row in grid)

        # 能否水平分割
        def calc(a: List[List[int]]) -> bool:
            m, n = len(a), len(a[0])

            def f() -> bool:
                st = {0}  # 0 對應不删除數字
                s = 0
                for i, row in enumerate(a[:-1]):
                    for j, x in enumerate(row):
                        s += x
                        # 第一行，不能删除中間元素
                        if i > 0 or j == 0 or j == n - 1:
                            st.add(x)
                    # 特殊處理只有一列的情況，此時只能刪除第一個數或者分割線上那個數
                    if n == 1:
                        if s * 2 == total or s * 2 - total == a[0][0] or s * 2 - total == row[0]:
                            return True
                        continue
                    if s * 2 - total in st:
                        return True
                    # 如果分割到更下面，那麼可以删第一行的元素
                    if i == 0:
                        st.update(row)
                return False

            if f():
                return True
            a.reverse()
            return f()

        # 水平分割 or 垂直分割
        return calc(grid) or calc(list(zip(*grid)))
