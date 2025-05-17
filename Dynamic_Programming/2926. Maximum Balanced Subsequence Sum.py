# TC:O(nlgn+n) SC:O(n)
class FenwickTree:
    def __init__(self, n: int):
        self.tree = [-inf] * (n + 1) 
    def update(self, i: int, val: int) -> None:
        while i < len(self.tree):
            if val > self.tree[i]:
                self.tree[i] = val
            i += i & -i
    def pre(self, i: int) -> int:
        res = -inf
        while i > 0:
            if self.tree[i] > res:
                res = self.tree[i]
            i &= i - 1
        return res
    # def query(self, l: int, r: int) -> int:
    #     if r < l:
    #         return 0
    #     return self.pre(r) - self.pre(l - 1)
class Solution:
    def maxBalancedSubsequenceSum(self, nums: List[int]) -> int:
        '''
        換句話說 一定要選遞增的 兩者val 相減 >= index相減
        一個數字也被認為是合法的 要找出sum最大的子序列
        子序列問題 相鄰相關 -> 枚舉選哪個 n ^ 2 不能通過此題
        換一種角度想 會往貪心 or 觀察題目性質找到O(n) 去想
        我會希望往前找的時候找前面比我小 並且離我越近越好的
        數字一樣那肯定越近越好 
        數字越小越往後放，他能夠被其他的越能夠接納
        cur - prev >= cur_pos - prev_pos -> cur - cur_pos >= prev - prev_pos
        會想到單調棧來做這題
        重點都是在求說小於等於目前數值的數字中找出最大值跟我匹配，然後動態去改動比我大的那些值
        算是單點查詢 單點更新 可以做最大最小值 by BIT
        '''
        #樹狀數組BIT
        arr = sorted(set(x - i for i, x in enumerate(nums)))
        bit = FenwickTree(len(arr))
        for i in range(len(nums)):
            j = bisect_left(arr, nums[i] - i) + 1
            p = bit.pre(j) # 這點之前的最大值在哪
            if p != -inf:
                # 選 or 不選
                p = p + nums[i]if p + nums[i] > nums[i] else nums[i]
            else:
                p = nums[i]
            bit.update(j, p)
        return bit.pre(len(arr))
        '''
        # 單調棧
        n = len(nums)
        sd = SortedDict() # 相當於C++ map<int,int>
        ans = -inf
        for i in range(n):
            x = nums[i] - i
            j = sd.bisect_right(x)
            if j > 0:
                prev_key = sd.keys()[j - 1]
                sd[x] = sd[prev_key] + nums[i] if sd[prev_key] + nums[i] > nums[i] else nums[i]
            else:
                sd[x] = nums[i]
            ans = max(ans, sd[x])
            j = sd.bisect_right(x)
            while j < len(sd) and sd.peekitem(j)[1] <= sd[x]:
                sd.popitem(j)
        return ans
        '''
