# TC:O(k) SC:O(1)
class Solution:
    def countVisiblePeople(self, n: int, pos: int, k: int) -> int:
        '''
        右邊的看得到我選L
        左邊的看得到我選R
        問說pos的人可以看得到剛好k個人的選法有幾種
        '''
        MOD = 10**9 + 7
        ans = comb(n - 1, k) % MOD

        return (ans * 2) % MOD
