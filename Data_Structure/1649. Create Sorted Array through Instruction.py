# TC:O(nlgn) SC:O(n) SotedList
class Solution:
    def createSortedArray(self, instructions: List[int]) -> int:
        sl = SortedList()
        MOD = 10 ** 9 + 7
        ans = 0
        for x in instructions:
            sm = sl.bisect_left(x)
            lg = len(sl) - sl.bisect_right(x)
            ans = (ans + min(sm, lg)) % MOD
            sl.add(x)
        return ans
