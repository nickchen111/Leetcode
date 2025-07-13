# TC:O(nlogn + mlogm) SC:O(1)
class Solution:
    def matchPlayersAndTrainers(self, players: List[int], trainers: List[int]) -> int:
        players.sort()
        trainers.sort()
        j = bisect_left(trainers, players[0])
        left = 0
        for i in range(j, len(trainers)):
            if left < len(players) and trainers[i] >= players[left]:
                left += 1
        return left
