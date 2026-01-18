class AuctionSystem:

    def __init__(self):
        self.amount = {} # (userId, itemId) : bidAmount
        self.item_h = defaultdict(list) # item -> (bidAmount, userId)
    def addBid(self, userId: int, itemId: int, bidAmount: int) -> None:
        self.amount[(userId, itemId)] = bidAmount
        heappush_max(self.item_h[itemId], (bidAmount, userId))

    def updateBid(self, userId: int, itemId: int, newAmount: int) -> None:
        self.addBid(userId, itemId, newAmount)

    def removeBid(self, userId: int, itemId: int) -> None:
        self.amount.pop((userId, itemId))

    def getHighestBidder(self, itemId: int) -> int:
        h = self.item_h[itemId]
        while h:
            bidder, userId = h[0]
            if bidder == self.amount.get((userId, itemId), None):
                return userId
            heappop_max(h)
        return -1


# Your AuctionSystem object will be instantiated and called as such:
# obj = AuctionSystem()
# obj.addBid(userId,itemId,bidAmount)
# obj.updateBid(userId,itemId,newAmount)
# obj.removeBid(userId,itemId)
# param_4 = obj.getHighestBidder(itemId)