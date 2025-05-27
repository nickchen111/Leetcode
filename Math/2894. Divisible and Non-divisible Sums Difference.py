class Solution:
    def differenceOfSums(self, n: int, m: int) -> int:
        '''
        將不能被m除的扣掉能被m除的總和
        '''
        tot = n * (n + 1) // 2
        can = sum(x if x % m == 0 else 0 for x in range(m, n + 1, m))
        return tot - 2 * can
