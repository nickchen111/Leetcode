# TC:O(n) SC:O(1)
class Solution:
    def minMoves(self, balance: List[int]) -> int:
        if sum(balance) < 0:
            return -1
        
        neg_idx = next((i for i, x in enumerate(balance) if x < 0), -1)
        if neg_idx == -1:
            return 0
        n = len(balance)
        need = -balance[neg_idx]
        ans = 0
        
        for dist in range(1, n):
            direction = -dist
            idx = (neg_idx + direction) % n
            if balance[idx] > 0:
                transfer = min(balance[idx], need)
                ans += transfer * dist
                need -= transfer
                if need == 0:
                    return ans
            direction = dist
            idx = (neg_idx + direction) % n
            if balance[idx] > 0:
                transfer = min(balance[idx], need)
                ans += transfer * dist
                need -= transfer
                if need == 0:
                    return ans
        return ans
