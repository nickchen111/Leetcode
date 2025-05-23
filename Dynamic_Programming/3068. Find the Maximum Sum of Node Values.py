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
        n = len(nums)
        g = [[] for _ in range(n)]
        for u, v in edges:
            g[u].append(v)
            g[v].append(u)
        def dfs(u: int, parent: int) -> (int, int):
            # 初始狀態：這個節點自己做/不做 XOR
            dp0 = nums[u]        # 偶數次 XOR，沒改 nums[u]
            dp1 = nums[u] ^ k    # 奇數次 XOR，改過 nums[u]

            for v in g[u]:
                if v == parent:
                    continue
                child0, child1 = dfs(v, u)
                new_dp0 = max(dp0 + child0, dp1 + child1)  # 偶數 XOR + 偶數，或奇數 + 奇數 = 偶數
                new_dp1 = max(dp0 + child1, dp1 + child0)  # 偶數 XOR + 奇數，或奇數 + 偶數 = 奇數

                dp0, dp1 = new_dp0, new_dp1
            return dp0, dp1
        res0, res1 = dfs(0, -1)
        return res0  # 我們只能選偶數次 XOR
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
