class Solution:
    def minimumHammingDistance(self, source: List[int], target: List[int], allowedSwaps: List[List[int]]) -> int:
        ans = 0
        n = len(source)
        pa = list(range(n))
        def find(x:int) -> int:
            if x != pa[x]:
                pa[x] = find(pa[x])
            return pa[x]
        def merge(x:int, y:int) -> int:
            x, y = find(x), find(y)
            if x > y:
                pa[x] = y
            else:
                pa[y] = x
        
        for x, y in allowedSwaps:
            merge(x, y) # index
        # index -> 數字 -> count
        mp = defaultdict(lambda:defaultdict(int))
        for i, x in enumerate(source):
            anc = find(i)
            mp[anc][x] += 1
        for i in range(n):
            anc = find(i)
            if mp[anc][target[i]] == 0:
                ans += 1
                continue
            mp[anc][target[i]] -= 1
        return ans



        