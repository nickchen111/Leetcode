# 單調棧 stack: TC:O((n + q) lgn + qlgq) SC:O(n) BIT: TC:O((n + q) * lg(n + q)) SC:O(n)
class FenwickTree:
    def __init__(self, n: int):
        self.tree = [-inf] * (n + 1) 
    def update(self, i: int, val: int) -> None:
        while i < len(self.tree):
            if val > self.tree[i]:
                self.tree[i] = val
            i += i & -i
    def pre(self, i: int) -> int:
        res = -1
        while i > 0:
            if self.tree[i] > res:
                res = self.tree[i]
            i &= i - 1
        return res
class Solution:
    def maximumSumQueries(self, nums1: List[int], nums2: List[int], queries: List[List[int]]) -> List[int]:
        '''
        兩個array 一些query 要找出 query中的 兩個數字 滿足以下條件
        nums1 >= x, nums2 >= y的 該index 有哪兩個加總會是最大的
        首先會想到 nums1[i] + nums2[i] 先加總好 然後query來 可以先判斷加總
        但還需要個別判斷是否雙方皆滿足此條件
        暴力解 就是逐個找 每個滿足的index 然後看兩者交集有哪些index 最後去看看這些index加總最大值是多少?
        這裡能夠拆解優化的地方是?
        從另一個角度看  query 可以先排序 按照 x值小到大 越大的時候 原本array上的一些就會被淘汰掉
        先比較x -> val 裡面在排序 小到大y的值 -> sum
        ''' 
        # 樹狀數組 離散化 + 相反數映射(後綴轉前綴)
        nums = sorted(((a,b) for (a, b) in zip(nums1, nums2)), key = lambda p: -p[0]) # x從大到小
        unique_set = SortedSet(b for (a,b) in nums)
        for (a, b) in queries:
            unique_set.add(b)
        n = len(unique_set)
        mp = {val : idx for idx, val in enumerate(unique_set)}
        bit = FenwickTree(n)
        ans = [-1] * len(queries)
        j = 0
        for i, (x, y) in sorted(enumerate(queries), key = lambda p: -p[1][0]):
            while j < len(nums) and x <= nums[j][0]: # x 滿足條件
                ax, ay = nums[j]
                bit.update(n - mp[ay], ax + ay)
                j += 1
            ans[i] = bit.pre(n - mp[y])
        return ans
        '''
        # 單調棧
        n = len(nums1)
        a = sorted(((a,b) for (a, b) in zip(nums1, nums2)), key = lambda p: -p[0]) # x從大到小
        st = []
        j = 0
        ans = [-1] * len(queries)
        for i, (x, y) in sorted(enumerate(queries), key=lambda p: -p[1][0]): # enumerate() 會讓index上多一個index (idx,原query)
            while j < n and x <= a[j][0]:
                # 判斷y狀況 先將 沒有比我總和大的踢出，因為總和比我小 前者x大 y 小 後者x小 y 肯定較大 如果後者加總比前者大
                ax, ay = a[j]
                while st and st[-1][1] <= ax + ay:
                    st.pop()
                if not st or st[-1][0] < ay:
                    st.append((ay, ax + ay))
                j += 1
            p = bisect_left(st, (y, ))
            if p < len(st):
                ans[i] = st[p][1]
        return ans
        '''
            
