# TC:O(n + log(n + q) + 均攤log(n+q)) SC:O(n + q)
class EventManager:
    def __init__(self, events: List[List[int]]):
        self.id_to_priority = {}
        self.h = []
        for eid, priority in events:
            self.id_to_priority[eid] = priority
            self.h.append((-priority, eid))
        heapify(self.h)

    def updatePriority(self, eventId: int, newPriority: int) -> None:
        self.id_to_priority[eventId] = newPriority
        heappush(self.h, (-newPriority, eventId))

    def pollHighest(self) -> int:
        while self.h:
            priority, eid = heappop(self.h)
            if self.id_to_priority.get(eid, -1) == -priority:
                del self.id_to_priority[eid]
                return eid
        return -1
            


# Your EventManager object will be instantiated and called as such:
# obj = EventManager(events)
# obj.updatePriority(eventId,newPriority)
# param_2 = obj.pollHighest()
