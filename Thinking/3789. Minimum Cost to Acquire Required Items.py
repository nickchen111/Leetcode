# TC:O(1) SC:O(1)
class Solution:
    def minimumCost(self, cost1: int, cost2: int, costBoth: int, need1: int, need2: int) -> int:
        if costBoth >= cost1 + cost2:
            return cost1 * need1 + cost2 * need2
        mn = min(need1, need2)
        cand = mn * costBoth
        if need1 == mn and cost2 <= costBoth:
            return cand + (need2 - mn) * cost2
        if need2 == mn and cost1 <= costBoth:
            return cand + (need1 - mn) * cost1
        return costBoth * max(need1, need2)
        
