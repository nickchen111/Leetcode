# TC:O(n * n * lgn) SC:O(n)
class FenwickTree:
    def __init__(self, n: int):
        self.tree = [0] * (n + 1) 
    def update(self, i: int, val: int) -> None:
        while i < len(self.tree):
            self.tree[i] += val
            i += i & -i

    def pre(self, i: int) -> int:
        res = 0
        while i > 0:
            res += self.tree[i]
            i &= i - 1
        return res
    def query(self, l: int, r: int) -> int:
        if r < l:
            return 0
        return self.pre(r) - self.pre(l - 1)
class Solution:
    def countGoodTriplets(self, arr: List[int], a: int, b: int, c: int) -> int:
        '''
        這種首先讓我想到前後綴分解
        i, j, k
        arr[i] - arr[j] <= a
        -a + arr[j] <= arr[i] <= a + arr[j]
        abs(5 - 3) <= 2
        abs(3 - 5) <= 2
        找出來的這些點 再去比較是否兩者相減會是 <= c 又要n^2 所以failed
        再想到因為邊走邊需要查找之前的點，會去動態刪除走過的元素，並且要去查找剩餘元素有多少點超過某些數值 -> BIT 可以做到動態修改lgn, 以及查詢lgn，針對區間查詢這題可以做兩次查詢即可
        要說的話也不算差分創建的BIT，算是單點修改，以及區間查詢
        |arr[i] - arr[j]| <= a 已知訊息
        |arr[j] - arr[k]| <= b 可以拆解成 b + arr[j] >= arr[k] >= arr[j] - b
        |arr[i] - arr[k]| <= c 拆解成 c + arr[i] >= arr[k] >= arr[i] - c
        '''
        n = len(arr)
        mx = max(arr) # 有可能是0 需要+1
        bit = FenwickTree(mx + 1)
        ans = 0
        for x in arr:
            bit.update(x + 1, 1)
        for j in range(n):
            bit.update(arr[j] + 1, -1)
            for i in range(j):
                if abs(arr[i] - arr[j]) <= a:
                    lo = max(arr[j] - b, arr[i] - c)
                    hi = min(arr[j] + b, arr[i] + c)
                    lo = max(lo, 0)
                    hi = min(hi, mx)
                    if lo <= hi:
                        ans += bit.query(lo + 1, hi + 1)
        return ans
