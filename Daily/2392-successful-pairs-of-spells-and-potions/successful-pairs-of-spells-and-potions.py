class Solution:
    def successfulPairs(self, spells: List[int], potions: List[int], success: int) -> List[int]:
        # 向上取整
        potions.sort()
        n = len(potions)
        ans = []
        for i in range(len(spells)):
            target = (success - 1) // spells[i] + 1
            j = bisect_left(potions, target)
            ans.append(n - j)
        return ans
