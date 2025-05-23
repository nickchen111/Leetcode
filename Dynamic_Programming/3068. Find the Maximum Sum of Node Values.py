# TC:O(n) SC:O(1)
class Solution:
    def maximumValueSum(self, nums: List[int], k: int, edges: List[List[int]]) -> int:
        '''
        貪心nlgn可解的題 但如果是要用DP呢？
        首先我會想先將樹結構退化到一條鏈 判斷當下的點是否需要做XOR 如果需要的話他後面必須要有點 否則無法做
        換成二叉樹就是判斷一下做了以後後面每個點的狀況加總哪個是最大的
        因此每個點的狀況可以是 走到該點時 用了 odd or even次的XOR 該點用or 不用 可以產生的最大值
        '''

        '''
        XOR 兩次等於沒變, 所以這題完全可以說是問說XOR偶數次可以得到的最大值是多少
        f[i][j] : 走到i為止 XOR odd or even 的最大元素和是多少
        f[i][0] = max(f[i-1][0] + x, f[i-1][1] + (x ^k))
        f[i][1] = max(f[i-1][1] + x, f[i-1][0] + (x ^k))
        '''
        # 空間優化
        f0, f1 = 0, -inf
        for x in nums:
            f0, f1 = max(f0 + x, f1 + (x ^ k)), max(f1 + x, f0 + (x ^ k))
        return f0

        '''
        遞推
        n = len(nums)
        f = [[-inf] * 2 for _ in range(n+1)]
        f[0][0] = 0
        for i in range(n):
            x = nums[i]
            f[i+1][0] = max(f[i][0] + x, f[i][1] + (x ^ k))
            f[i+1][1] = max(f[i][1] + x, f[i][0] + (x ^ k))
        return f[n][0]
        '''

        '''
        遞歸 其實不需要建圖
        g = [[] for _ in nums]
        for x, y in edges:
            g[x].append(y)
            g[y].append(x)

        def dfs(x: int, fa: int) -> Tuple[int, int]:
            f0, f1 = 0, -inf  # f[x][0] 和 f[x][1]
            for y in g[x]:
                if y != fa:
                    r0, r1 = dfs(y, x)
                    f0, f1 = max(f0 + r0, f1 + r1), max(f1 + r0, f0 + r1)
            return max(f0 + nums[x], f1 + (nums[x] ^ k)), max(f1 + nums[x], f0 + (nums[x] ^ k))
        return dfs(0, -1)[0]
        '''


        '''
        貪心
        arr = []
        for i in range(n):
            arr.append((nums[i] ^ k) - nums[i])
        arr.sort(reverse = True)
        ans = sum(nums)
        for i in range(1, n, 2):
            if arr[i] + arr[i - 1] > 0:
                ans += arr[i] + arr[i - 1]
        return ans
        '''
