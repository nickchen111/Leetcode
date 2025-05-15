# SortedList or multiset: TC:O(nlgn) SC:O(n) Array: TC:O(50 * n) SC:O(100)  BIT: TC:O(nlgnlgn) SC:O(n)
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
    def getSubarrayBeauty(self, nums: List[int], k: int, x: int) -> List[int]:
        '''
        去找每個定長的subarray 第 x 小的負數 如果少於x個neg就是0
        1. sliding window 並且需要維護最小值 會想到啥? 
        a. set C++
        b. SortedList 直接去二分 python
        c. array 從值域下手 去判斷是否有超過x個neg
        2. 一樣做 sliding window 但是用樹狀數組去存 存完對樹狀數組做二分判斷第X小的數字是啥 
        '''
        n = len(nums)
        # BIT 需離散化 一樣數字直接去重 重新定義下標即可
        mp = {x : i + 1 for i, x in enumerate(sorted(set(nums)))}
        arr = sorted(mp.keys())
        bit = FenwickTree(n)
        for num in nums[:k-1]:
            bit.update(mp[num], 1)
        def xth(x : int) -> int:
            l, r = 1, n # x th 小的數值在哪個1-index上
            while l < r:
                mid = (r + l) // 2
                if bit.pre(mid) >= x:
                    r = mid
                else:
                    l = mid + 1
            return min(0, arr[l-1])

        ans = [0] * (n - k + 1)
        for i in range(k-1, n):
            bit.update(mp[nums[i]], 1) # 進入窗口
            # 二分
            ans[i - k + 1] = xth(x)
            bit.update(mp[nums[i - k + 1]], -1) # 出窗
        return ans

        '''
        # array值域 做法
        cnt = [0] * 101
        ans = [0] * (n - k + 1)
        for num in nums[:k - 1]:
            cnt[num] += 1
        for i, (in_, out) in enumerate(zip(nums[k - 1:], nums)):
            cnt[in_] += 1
            left = x
            for j in range(-50, 0):
                left -= cnt[j]
                if left <= 0:
                    ans[i] = j
                    break
            cnt[out] -= 1
        return ans
        '''
            
        '''
        # SortedList
        sl = SortedList()
        i = 0
        ans = []
        for j in range(n):
            sl.add(nums[j])
            if j >= k - 1:
                sm_x = sl[x - 1]
                if sm_x < 0:
                    ans.append(sm_x)
                else:
                    ans.append(0)
            if j - i + 1 == k:
                sl.remove(nums[i])
                i += 1
        return ans
        '''
