# TC:O(nlgn) SC:O(n)
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
    def minInteger(self, num: str, k: int) -> str:
        '''
        拿到這題剛開始想的會是盡量將越前面的數字換得越小越好
        換的次數k， k == 1e9 , n = 3e4
        會想說每個數字去往後看，看後面最小的數字是多少?
        但是每次都走一次去看會是 n^2 時間複雜度
        是否有更快的方法去判斷? 可以用BIT 去lgn 查後面較小的數字 但是要滿足距離 小於等於 當前剩餘操作次數
        並且還要找到最小的那個數字
        設計的資料結構會是
        1 : pos1, pos2... 由小到大
        2 : pos1, pos2... 
        走完之後還需要刪除他
        馬上想到的是python sortelist 但是實作上 有點難處理swap後 後面數字都要一起移動index的問題
        這段轉移是樹狀數組的區間查詢 那就看這段轉移之間查找的數字就要往後移幾次
        由於每次都一定是選 最前面的數字 直接用deque 模擬前後狀況即可
        算是單點更新 區間查詢
        '''
        n = len(num)
        pos = [deque() for _ in range(10)]
        num = [ord(ch) - ord('0') for ch in num]
        for i, x in enumerate(num):
            pos[x].append(i + 1)
        ans = ""
        bit = FenwickTree(n)
        for i in range(1, n + 1):
            for j in range(10): # 比i小的數字
                # 需要替換掉 目前的數字到後面去 然後將替換過來的數字移除掉
                if pos[j]:
                    behind = bit.query(pos[j][0] + 1, n) # 這段之間如果有人交換的話他就會後移
                    dist = pos[j][0] + behind - i
                    if dist <= k:
                        bit.update(pos[j].popleft(), 1)
                        ans += str(j)
                        k -= dist
                        break
        return ans
