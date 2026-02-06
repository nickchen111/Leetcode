# 斜率優化 TC:O(k * n) SC:O(n)
class Vec:
    __slots__ = 'x', 'y'

    def __init__(self, x: int, y: int):
        self.x = x
        self.y = y

    def __sub__(self, b: "Vec") -> "Vec":
        return Vec(self.x - b.x, self.y - b.y)

    def det(self, b: "Vec") -> int:
        return self.x * b.y - self.y * b.x

    def dot(self, b: "Vec") -> int:
        return self.x * b.x + self.y * b.y


class Solution:
    def minPartitionScore(self, nums: List[int], k: int) -> int:
        n = len(nums)
        pre = list(accumulate(nums, initial=0))
        f = [0] + [inf] * n

        for K in range(1, k + 1):
            s = pre[K - 1]
            q = deque([Vec(s, f[K - 1] + s * s - s)])
            for i in range(K, n - (k - K) + 1):  # 其他子数组的长度至少是 1
                s = pre[i]
                p = Vec(-2 * s, 1)
                # 這段while就是在講說現在是遞減的話 左邊的向量肯定比右邊更遠 你就可以出雙端隊列了
                while len(q) > 1 and p.dot(q[0]) >= p.dot(q[1]): 
                    q.popleft()

                v = Vec(s, f[i] + s * s - s)
                f[i] = p.dot(q[0]) + s * s + s
                # 這段就是在判斷是不是下凸包上的邊界點
                while len(q) > 1 and (q[-1] - q[-2]).det(v - q[-1]) <= 0:
                    q.pop()
                q.append(v)

        return f[n] // 2


# 分治 個人覺得簡單很多 TC:O(k * n * logn) SC:O(n)
class Solution:
    def minPartitionScore(self, nums: List[int], k: int) -> int:
        n = len(nums)
        presum = list(accumulate(nums, initial=0))
        
        dp = [inf] * (n + 1)
        dp[0] = 0
        
        for kk in range(1, k + 1):
            new_dp = [inf] * (n + 1)
            def solve(L:int, R:int, pos_L:int, pos_R:int) -> None:
                if L > R:
                    return
                
                mid = (L + R) // 2
                best_j = -1
                
                for j in range(pos_L, min(mid, pos_R + 1)):
                    cur = presum[mid] - presum[j]
                    score = dp[j] + cur * (cur + 1) // 2
                    if score < new_dp[mid]:
                        new_dp[mid] = score
                        best_j = j
                
                solve(L, mid - 1, pos_L, best_j)
                solve(mid + 1, R, best_j, pos_R)

            solve(kk, n, kk - 1, n - 1)
            dp = new_dp
            
        return dp[n]
