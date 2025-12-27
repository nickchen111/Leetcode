class Solution:
    def mostBooked(self, n: int, meetings: List[List[int]]) -> int:
        '''
        需要用ds 去搜集沒執行到的meeting, 記錄房間執行次數, 哪些房間可以使用(最低是誰), 使用中的房間何時結束(endTime, roomId)
        沒執行的meetings 已經按照順序放進ds -> deque 從頭開始用
        房間使用次數 -> array
        可以使用房間 -> pq
        何時結束 -> pq
        '''
        meetings.sort()
        pq = []
        st = list(range(n))
        cnt = [0] * n
        maxCount = ans = 0
        for start, end in meetings:
            # 可釋放出來的房間
            while pq and pq[0][0] <= start:
                _, room = heappop(pq)
                heappush(st, room)
            duration = end - start
            if len(st) > 0:
                room = heappop(st)
                heappush(pq, (end, room))
            else:
                lastEnd, room = heappop(pq)
                heappush(pq, (lastEnd + duration, room))
            cnt[room] += 1
            if cnt[room] > maxCount:
                maxCount = cnt[room]
                ans = room
            elif cnt[room] == maxCount and ans > room:
                ans = room
        return ans