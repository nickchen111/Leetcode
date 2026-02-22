# TC:O(n^4) SC:O(n^4)
class Solution:
    def primeFactorization(self, k: int) -> Tuple[Tuple[int, int, int], bool]:
        e2 = (k & -k).bit_length() - 1
        k >>= e2

        e3 = 0
        while k % 3 == 0:
            e3 += 1
            k //= 3

        e5 = 0
        while k % 5 == 0:
            e5 += 1
            k //= 5

        return (e2, e3, e5), k == 1

    def countSequences(self, nums: List[int], k: int) -> int:
        (e2, e3, e5), ok = self.primeFactorization(int(k))
        if not ok:
            return 0

        es = [self.primeFactorization(x)[0] for x in nums]

        @cache
        def dfs(i: int, e2: int, e3: int, e5: int) -> int:
            if i < 0:
                return 1 if e2 == e3 == e5 == 0 else 0

            x, y, z = es[i]
            res1 = dfs(i - 1, e2 - x, e3 - y, e5 - z)
            res2 = dfs(i - 1, e2 + x, e3 + y, e5 + z)
            res3 = dfs(i - 1, e2, e3, e5)
            return res1 + res2 + res3

        return dfs(len(nums) - 1, e2, e3, e5)

# gcd 
class Solution:
    def countSequences(self, nums: List[int], k: int) -> int:
        @cache
        def dfs(i: int, p: int, q: int) -> int:
            if i < 0:
                return 1 if p == k and q == 1 else 0

            x = nums[i]
            g = gcd(p, q * x)
            res1 = dfs(i - 1, p // g, q * x // g)
            g = gcd(p * x, q)
            res2 = dfs(i - 1, p * x // g, q // g)
            res3 = dfs(i - 1, p, q)
            return res1 + res2 + res3

        return dfs(len(nums) - 1, 1, 1)

# 賽時我的寫法
class Solution:
    def countSequences(self, nums: list[int], k: int) -> int:
        n = len(nums)
        
        @cache
        def dfs(idx:int, cur_val:float): # 2, 3, 5 質因數分解
            if idx == n:
                return 1 if abs(cur_val - k) < 1e-7 else 0
            return (dfs(idx + 1, cur_val * nums[idx]) + 
                    dfs(idx + 1, cur_val / nums[idx]) + 
                    dfs(idx + 1, cur_val))

        return dfs(0, 1.0)
