# TC:O(nlgn + mlgm + min(lgn, lgm) * lg(min(n,m))) SC:O(min(n,m))
class Solution:
    def maxTaskAssign(self, tasks: List[int], workers: List[int], pills: int, strength: int) -> int:
        '''
        要分配工作給可以做的員工，問說最多可以分配多少工作出去
        這題主要是藥丸的分配 如果現在有可能吃藥丸獲得任務的是否要用 不用他可能可以解一個別人不能解的任務 然後讓後面任物都可以解
        用了可能只能解當下任務，但後面一系列任務無法解 因為沒有藥丸了
        n = m = 5 * 1e4
        '''
        tasks.sort()
        n = len(tasks)
        workers.sort()
        def check(k:int) -> bool:
            i, p = 0, pills
            valid_tasks = deque()
            for w in workers[-k:]: # 由小到大取最強的k worker 他們都要在力所能及去解決問題
                while i < n and w + strength >= tasks[i]:
                    valid_tasks.append(tasks[i])
                    i += 1
                if not valid_tasks:
                    return False
                if w >= valid_tasks[0]: # 當前的worker能解決最簡單的 後面的人也可以靠著吃藥解決其餘任務
                    valid_tasks.popleft()
                    continue
                if p == 0:
                    return False
                p -= 1
                valid_tasks.pop()
            return True

        '''
        需要二分再二分的寫法
        def check(target:int) -> bool:
            if target > len(workers):
                return False
            ans = 0
            cnt = pills
            sl = SortedList(workers)
            for j in range(target - 1, -1, -1):
                x = tasks[j]
                if sl[-1] >= x:
                    sl.remove(sl[-1])
                else:
                    if cnt == 0: return False
                    j = sl.bisect_left(x - strength)
                    if j == len(sl): return False
                    cnt -= 1
                    sl.remove(sl[j])
            return True
        '''

        l, r = 0, min(len(workers), len(tasks))
        while l < r:
            mid = (l + r + 1) // 2
            if check(mid):
                l = mid
            else:
                r = mid - 1
        return l
