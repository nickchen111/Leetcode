class Solution:
    def countMentions(self, numberOfUsers: int, events: List[List[str]]) -> List[int]:
        events.sort(key=lambda e: (int(e[1]), e[0][2]))
        online = [0] * numberOfUsers
        ans = [0] * numberOfUsers
        cnt = 0
        for event in events:
            time = int(event[1])
            if event[0] == "MESSAGE":
                if event[2][0] == "A":
                    cnt += 1
                elif event[2][0] == "H":
                    for i in range(numberOfUsers):
                        if online[i] <= time:
                            ans[i] += 1
                else:
                    for s in event[2].split():
                        ans[int(s[2:])] += 1
            else:
                online[int(event[2])] = int(event[1]) + 60
        if cnt:
            for i in range(numberOfUsers):
                ans[i] += cnt
        return ans

                    

