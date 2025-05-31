# 樹狀數組 TC:O(n * k + nlgn) SC:O(n) 貪心 + 暴力 TC:O(n * (n + k)) SC:O(n)
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
    def getMinSwaps(self, num: str, k: int) -> int:
        '''
        permutation需要比當下數字大
        問說第k小的是哪個數字後 並且原始數字要翻轉幾次才能變成該數字
        翻轉只能鄰居翻 
        變成有序的最小交換次數:
        1. 任意兩項交換 置換環 n - 聯通塊個數
        2. 相鄰兩項交換 逆序對 樹狀數組 or 歸併排序
        以這題來說就是找到kth個之後就用它去枚舉後面有多少個比他小的數字
        這題看起來要判斷一下如何確定移動之後剩餘數字是否需要移動 如何判斷?
        當前修改後的位置 對應回我原本在的位置，必須判斷我需要移動的這段距離之間有多少個字元卡在中間
        算是一種區間查詢 然後單點修改 所以可以用樹狀數組
        至於要如何轉成逆序對問題 這裡就要用下標表示法
        原下標12345.... 然後判斷一下更改之後的下標狀況 去求更改後的下標要多少次可以變成排序後的下標 -> 逆序對
        '''
        ne = list(num)
        n = len(num)
        # 找到第 k 個排列 n * k
        def next_premutation(arr:List[int]) -> bool:
            i = len(arr) - 2
            while i >= 0 and arr[i] >= arr[i + 1]:
                i -= 1
            if i == -1:
                return False
            j = len(arr) - 1
            while arr[j] <= arr[i]:
                j -= 1
            arr[i], arr[j] = arr[j], arr[i]
            arr[i + 1:] = reversed(arr[i + 1:])
            return True
        # 樹狀數組
        for _ in range(k):
            next_premutation(ne)
        pos = [[] for _ in range(10)] # 每個數字對應的位置
        trans = {x : ord(x) - ord('0') for x in '0123456789'}
        ne.reverse() # ne = list(reversed(ne))
        for i in range(len(ne)): # 從後往前 並且加入最前面的index到後面去 或者也可以用queue
            pos[trans[ne[i]]].append(n - 1 - i)
        nums = []
        for i in range(n):
            nums.append(pos[trans[num[i]]][-1])
            pos[trans[num[i]]].pop()
        bit = FenwickTree(n)
        ans = 0
        for i, x in enumerate(nums):
            ans += i - bit.pre(x + 1)
            bit.update(x + 1, 1)
        return ans
        '''
        # 貪心 + 暴力交換
        num_k = num[:]
        ans = 0
        for i in range(n):
            if num[i] != ne[i]:
                for j in range(i + 1, n):
                    if ne[j] == num_k[i]:
                        for k in range(j - 1, i - 1, -1):
                            ans += 1
                            ne[k], ne[k + 1] = ne[k + 1], ne[k]
                        break
        return ans
        '''
