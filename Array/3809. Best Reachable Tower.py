# TC:O(n) SC:O(1)
class Solution:
    def bestTower(self, towers: List[List[int]], center: List[int], radius: int) -> List[int]:
        '''
        找出距離center 在radius內最大q的towers位置
        '''
        ans = (inf, -1, -1)
        for tx, ty, q in towers:
            if abs(tx - center[0]) + abs(ty - center[1]) <= radius:
                ans = min(ans, (-q, tx, ty))
        return [ans[1], ans[2]]
