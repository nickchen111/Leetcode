# TC:O(nlogn) SC:O(n)
class Solution:
    def toggleLightBulbs(self, bulbs: list[int]) -> list[int]:
        cnt = Counter(bulbs)
        return sorted(k for k, v in cnt.items() if v % 2)
