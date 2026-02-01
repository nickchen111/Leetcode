# TC:O(1) SC:O(n)
class RideSharingSystem:

    def __init__(self):
        self.drivers = deque()
        self.riders = deque()
        self.online_riders = set()

    def addRider(self, riderId: int) -> None:
        self.riders.append(riderId)
        self.online_riders.add(riderId)

    def addDriver(self, driverId: int) -> None:
        self.drivers.append(driverId)

    def matchDriverWithRider(self) -> List[int]:
        if not self.drivers:
            return [-1, -1]
        while self.riders:
            p = self.riders[0]
            if p in self.online_riders:
                rider_id = self.riders.popleft()
                driver_id = self.drivers.popleft()
                self.online_riders.remove(rider_id)
                return [driver_id, rider_id]
            else:
                self.riders.popleft()
        return [-1, -1]

    def cancelRider(self, riderId: int) -> None:
        # 爛系統 不在系統的乘客也可以取消訂單
        self.online_riders.discard(riderId)
        # if riderId in self.online_riders:
        #     self.online_riders.remove(riderId)
"""
需要快速找出最早進到系統的available driver 與最早就在等待的rider
"""

# Your RideSharingSystem object will be instantiated and called as such:
# obj = RideSharingSystem()
# obj.addRider(riderId)
# obj.addDriver(driverId)
# param_3 = obj.matchDriverWithRider()
# obj.cancelRider(riderId)
