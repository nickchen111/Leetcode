# Greedy TC:O(n) SC:O(n)
class Solution:
    def minSwaps(self, nums: List[int]) -> int:
        pos1 = [i for i,x in enumerate(nums) if x % 2]
        n = len(nums)
        m = len(pos1)
        if abs(n - 2 * m) > 1:
            return -1
        def cal(start:int) ->int:
            if (n - start + 1) // 2 != m:
                return inf
            return sum(abs(i - j) for i, j in zip(range(start, n, 2), pos1))
        return min(cal(0), cal(1))
        
# 樹狀數組 TC:O(nlgn) SC:O(n)
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
    def minSwaps(self, nums: List[int]) -> int:
        '''
        所有數字皆不同 如果一個數字想找人換 就要找右邊最近的去交換
        先把所有數字按照odd even 歸類 然後按照順序填入 就是最後會有的結果
        用這個結果去藉由樹狀數組判斷
        '''
        odd, even = [], []
        for x in nums:
            if x % 2:
                odd.append(x)
            else:
                even.append(x)
        if abs(len(odd) - len(even)) > 1:
            return -1
        arr = []
        # 判斷從哪個開始收集 一開始odd or even
        def helper(flag: bool) -> None:
            nonlocal arr
            i = j = 0
            if flag:
                while i < len(odd) and j < len(even):
                    if (len(arr) % 2) == 0:
                        arr.append(odd[i])
                        i += 1
                    else:
                        arr.append(even[j])
                        j += 1
            else:
                while i < len(odd) and j < len(even):
                    if (len(arr) % 2) == 0:
                        arr.append(even[j])
                        j += 1
                    else:
                        arr.append(odd[i])
                        i += 1
            if i < len(odd):
                arr.append(odd[i])
            if j < len(even):
                arr.append(even[j])
            return arr
        def determine(flag: bool) -> int:
            ans = 0
            arr = helper(flag)           
            mp = defaultdict(int)
            for i,x in enumerate(arr):
                mp[x] = i
            bit = FenwickTree(len(arr))
            for i, x in enumerate(nums):
                idx = mp[x]
                # 目前有多少個數字 i個在裡面 找多少個小於我 bit.pre -> 多少個大於我就知道了
                ans += i - bit.pre(idx + 1)
                bit.update(idx + 1, 1)
            return ans
        ans = min(determine(True), determine(False))
        return ans
        
        
