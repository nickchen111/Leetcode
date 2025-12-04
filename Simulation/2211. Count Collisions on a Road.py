# TC:O(n) SC:O(1)
class Solution:
    def countCollisions(self, directions: str) -> int:
        directions = directions.lstrip('L')
        directions = directions.rstrip('R')
        return sum(1 for c in directions if c != 'S')
