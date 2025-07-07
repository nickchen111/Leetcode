# heap: TC:O(nlogn) SC:O(n)  UF: TC:O(nlogn + n) SC:O(n)
class Solution:
    def maxEvents(self, events: List[List[int]]) -> int:
        '''
        貪心的選較短的較早開始的
        '''
        events.sort(key = lambda x:x[1])
        # UF
        mx = events[-1][1]
        fa = list(range(mx + 2))
        def find(x: int) -> int:
            if fa[x] != x:
                fa[x] = find(fa[x])
            return fa[x]
        ans = 0
        for start, end in events:
            x = find(start)
            if x <= end:
                ans += 1
                fa[x] = x + 1
        return ans
        '''
        events.sort()
        heap = []
        day = 1
        last_day = max(e[1] for e in events)
        ans = 0
        i = 0
        while day <= last_day:
            while i < len(events) and events[i][0] == day:
                heappush(heap, events[i][1])
                i += 1
            while heap and heap[0] < day:
                heappop(heap)
            if heap:
                ans += 1
                heappop(heap)
            day += 1
        return ans
        '''
