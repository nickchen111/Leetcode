# TC:O(m*m + m^3 * lgt) t = 最多10^9次數, m 為字母數量26 SC:O(26^2)
MOD = 10 ** 9 + 7
# a @ b 矩陣乘法
def Mul (a : List[List[int]], b : List[List[int]]) -> List[List[int]]:
    return [[sum(x * y for x, y in zip(row, col)) % MOD for col in zip(*b)] for row in a]
# a^n @ f0 矩陣快速冪
def pow_mul (a: List[List[int]], n : int, f0 : List[List[int]]) -> List[List[int]]:
    ans = f0
    while n:
        if n & 1:
            ans = Mul(a, ans)
        a = Mul(a, a)
        n >>= 1
    return ans
class Solution:
    def lengthAfterTransformations(self, s: str, t: int, nums: List[int]) -> int:
        SIZE = 26
        # 答案 = (遞推式 ^ t) * 初始值(全為1的列向量)
        f0 = [[1] for _ in range(SIZE)] # 邊界條件 初始值
        m = [[0] * SIZE for _ in range(SIZE)]
        for i,c in enumerate(nums):
            for j in range(i + 1, i + c + 1):
                m[i][j % 26] += 1
        mt = pow_mul(m, t, f0)
        ans = 0
        for ch, cnt in Counter(s).items():
            ans += mt[ord(ch) - ord('a')][0] * cnt # 會是26 * 1 的矩陣所以取0 index
        return ans % MOD

  # 可以過上一題的寫法
  class Solution:
    def lengthAfterTransformations(self, s: str, t: int) -> int:
        MOD = 10 ** 9 + 7
        dq = deque([0] * 26)
        for c in s:
            dq[ord(c) - ord('a')] += 1
        for i in range(t):
            z = dq.pop()
            dq[0] += z
            dq.appendleft(z)
        return sum(dq) % MOD
