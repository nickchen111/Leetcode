class Solution:
    def minDifference(self, n: int, k: int) -> List[int]:
        '''
        用k個數字相乘可以是n，並且這些數字任兩個diff要進量小 -> 二分
        首先要猜最大跟最小 這可以去對他做因數分解 -> 2^16 ~= 1e5
        16個去搭配選or不選
        '''
        def get_factors(x):
            facs = []
            for i in range(1, int(sqrt(x)) + 1):
                if x % i == 0:
                    facs.append(i)
                    if i != x // i:
                        facs.append(x // i)
            return sorted(facs)

        factors = get_factors(n)
        ans = []
        minDiff = inf
        
        # nonlocal ans
        def dfs(prod, count, path):
            nonlocal ans
            nonlocal minDiff
            if count == k:
                diff = max(path) - min(path)
                if prod == n and diff <= minDiff:
                    minDiff = diff
                    ans = path
                return

            for f in factors:
                if prod * f > n:
                    break
                if n % (prod * f) != 0:
                    continue
                dfs(prod * f, count + 1, path + [f])
        dfs(1, 0, [])
        return ans
        
        