# TC:O(nlogn) SC:O(1)
class Solution:
    def sortByBits(self, arr: List[int]) -> List[int]:
        arr.sort(key = lambda x : (x.bit_count(), x))
        return arr
