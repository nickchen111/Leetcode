class Solution:
    def isOneBitCharacter(self, bits: List[int]) -> bool:
        n = len(bits)

        i = 0
        while i < n - 1:
            if bits[i] == 0:
                i += 1
                continue
            i += 2
        return i == n - 1

        '''
        @cache
        def dfs(i:int) -> bool:
            if i == n - 1:
                return True
            if i == n:
                return False
            if bits[i] == 0:
                return dfs(i + 1)
            return dfs(i + 2)
        return dfs(0)
        '''