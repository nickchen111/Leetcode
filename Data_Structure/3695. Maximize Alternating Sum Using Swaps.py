# TC:O(nlogn) SC:O(n)
class UnionFind:
    def __init__(self, n: int):
        self._fa = list(range(n))
        
    def find(self, x: int) -> int:
        if self._fa[x] != x:
            self._fa[x] = self.find(self._fa[x])
        return self._fa[x]

    def merge(self, from_: int, to: int) -> None:
        x, y = self.find(from_), self.find(to)
        if x == y:
            return
        if x < y:
            self._fa[y] = x
        else:
            self._fa[x] = y
class Solution:
    def maxAlternatingSum(self, nums: List[int], swaps: List[List[int]]) -> int:
        '''
        最大化 偶數位置加總 - odd位置加總
        給你一段可以做的swap array 代表這些位置可以交換任意次 -> uf
        偶數大 odd小
        '''
        n = len(nums)
        uf = UnionFind(n)
        for x, y in swaps:
            uf.merge(x, y)
        mp = defaultdict(lambda: SortedList())
        for i in range(len(nums)):
            mp[uf.find(i)].add(nums[i])
        ans = 0
        for i in range(n):
            ancf = uf.find(i)
            if i % 2 == 0:
                ans += mp[ancf].pop(-1)
            else:
                ans -= mp[ancf].pop(0)
        return ans
