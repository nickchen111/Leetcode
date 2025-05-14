# 主要是按照val sort 下標後的巧秒計算跳過元素與下標轉換是重點
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
    def countOperationsToEmptyArray(self, nums: List[int]) -> int:
        '''
        n = 1e5 每次要先剔除最小的數字 不是最小的就往最後面放 nums中數字是獨特的 可以離散化
        跟之前某題排隊的好像 但這題只需要放到後面 不影響前面的操作
        所以感覺可以直接push_back增加array的長度 但如果剛好每個數字都要跑1e5 就會是1e10的時間複雜度...
        雖然理論上應該不太可能每一個都要跑1e5 但也可能被控在1e7之類 一樣超時
        想到可能需要想一個方式類似貢獻法的概念直接判斷出當下元素會需要跑幾輪後才會被收割到
        1. 好像就是看後面比他小的數字有多少個 加上他就會是答案?! -> 會導致後面數字誤判 因為他其實也有被加入後面中 不能直接刪除
        2. 當下數字要翻幾次 主要看他後面數字遞減序列多長?! 並且在不超過他為前提下
        => 上述想法都無法好好的解決本題，總會有設想不周到 或者 難以實作的部分
        這題來說要如何模擬一個數組的數字一直往後放，用下標來跑才是正解 因為可以一次略過從a點到b點loop的過程
        刪除一個數字後 下標自動往後一個數(free)
        記錄每個數的位置，從小到大刪除
        上一個刪除的位置會是pre, 當前需要刪除的下標會是i，從pre 到 i 需要移動幾次?
        1. 維護中間被刪除的元素個數 -> BIT
        如果 pre <= i: i - pre - query(pre, i) 就會是這次移動的cost
        如果 pre > i: n - pre - query(pre, n) + 1 (從n 到 1) + (i - 1) - query(1, i) 也就是要先從 pre 走到 n, n到1, 1走到i 可以簡化成:
        k - query(i + 1 or i, pre - 1) = query(pre, n) + query(1, i) 
        -> n - pre + i - (k - query(i, pre - 1))
        Python 也可以用SortedList
        這題額外還有挖掘更多性質的巧妙解法
        '''
        ans = n = len(nums)
        bit = FenwickTree(n)
        pre = 1 # 下標都從1 開始
        for k, i in enumerate(sorted(range(n), key = lambda i : nums[i])):
            i += 1
            if pre <= i:
                ans += i - pre - bit.query(pre, i)
            else:
                ans += n - pre + i - (k - bit.query(i, pre - 1))
            bit.update(i, 1)
            pre = i
        return ans
