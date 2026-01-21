# TC:O(n) SC:O(m) m 為元素種類
class Solution:
    def alternatingXOR(self, nums: List[int], target1: int, target2: int) -> int:
        '''
        block 之間xor結果要是 target1, target2, target1,...這樣的切分方法有多少種
        n = 1e5
        xor兩次等於沒有xor
        之前是湊出target2 要準備湊 target1 但目前數字是x的策略有多少個?
        之前是湊出target1 要準備湊 target2 但目前數字是x的策略有多少個?
        '''
        MOD = 10 ** 9 + 7
        mp2 = defaultdict(int)
        mp2[0] = 1
        mp1 = defaultdict(int)
        xor = 0
        ans = 0
        for i, x in enumerate(nums):
            xor ^= x
            t1 = xor ^ target1
            cand1 = mp2.get(t1, 0)
            t2 = xor ^ target2
            cand2 = mp1.get(t2, 0)
            if cand1 > 0:
                mp1[xor] = (mp1[xor] + cand1) % MOD
            if cand2 > 0:
                mp2[xor] = (mp2[xor] + cand2) % MOD
            ans = (cand1 + cand2) % MOD
        return (mp1[0] + mp2[0]) % MOD
            
