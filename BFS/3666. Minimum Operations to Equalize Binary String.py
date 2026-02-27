# TC:O(nlogn) SC:O(n)
class Solution:
    def minOperations(self, s: str, k: int) -> int:
        '''
        BFS作法
        因為可以看出0, 1數字的變化結果的狀態會是邊權為1的移動 遇到一樣的狀況就不用再做
        假設選了x個0 -> 0變化就是 z - x + (k - x) = z + k - 2 * x 此數學公式odd even靠 z + k 決定
        這樣來說還可以推導出 從 z 個 0 可以變化到的0數量的區間 需要求最小最大，將此區間移除，這段移除的時間複雜度會是 O(n)
        x >= 0, x <= k, x <= z, x >= k - (n - z) 至少要這麼多個0才能填滿k, -> [max(0, k - n + z), min(z, k))
        '''
        n = len(s)
        not_vis = [SortedList(range(0, n + 1, 2)), SortedList(range(1, n + 1, 2))]
        not_vis[0].add(n + 1) # 哨兵 下面while就不用判斷是否index越界
        not_vis[1].add(n + 1)

        start = s.count('0')
        not_vis[start % 2].discard(start)
        q = [start]
        ans = 0
        while q:
            tmp = q
            q = []
            for z in tmp: # z 代表有多少個0
                if z == 0:
                    return ans
                mn = z + k - 2 * min(z, k)
                mx = z + k - 2 * max(0, k - n + z)
                sl = not_vis[mn % 2]
                idx = sl.bisect_left(mn)
                while sl[idx] <= mx:
                    j = sl.pop(idx)
                    q.append(j)
            ans += 1
        return -1
