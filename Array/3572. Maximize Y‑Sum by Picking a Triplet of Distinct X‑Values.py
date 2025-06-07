# TC:O(n) SC:O(n)
class Solution:
    def maxSumDistinctTriplet(self, x: List[int], y: List[int]) -> int:
        '''
        選x都不相同的三個數字 然後挑出最大的三個可以選哪些
        '''
        mp = defaultdict(list)
        for i, num in enumerate(x):
            mp[num].append(i)
        mx, mx2, mx3 = 0, 0, 0
        for key, arr in mp.items():
            tmp = 0
            for idx in arr:
                if y[idx] > tmp:
                    tmp = y[idx]
            if tmp >= mx:
                mx2, mx, mx3 = mx, tmp, mx2
            elif tmp >= mx2:
                mx3, mx2 = mx2, tmp
            elif tmp > mx3:
                mx3 = tmp
        return mx + mx2 + mx3 if mx != 0 and mx2 != 0 and mx3 != 0 else -1
