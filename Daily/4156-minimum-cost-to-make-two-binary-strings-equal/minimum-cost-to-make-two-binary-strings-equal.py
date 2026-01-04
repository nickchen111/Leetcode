class Solution:
    def minimumCost(self, s: str, t: str, flipCost: int, swapCost: int, crossCost: int) -> int:
        '''
        a = 1, b = 3 -> avg = (a + b) // 2 來盡量增加swapCost
        01, 10, 10, 10 -> 0111, 1000
        a -> 01 對
        b -> 10 對
        先做串間交換 s[i] t[i]
        '''
        cnt = Counter(x + y for x, y in zip(s, t))
        a = cnt["01"]
        b = cnt["10"]
        if a > b:
            a, b = b, a
        cand1 = (a + b) * flipCost
        cand2 = (b - a) * flipCost + a * swapCost
        avg, mod = divmod(a + b, 2)
        cand3 = (avg - a) * crossCost + avg * swapCost + mod * flipCost
        return min(cand1, cand2, cand3) 
