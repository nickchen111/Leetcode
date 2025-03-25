# TC:O(n * m * lgU) SC:O(n * m * lgU)
class Solution:
    def minimumValueSum(self, nums: List[int], andValues: List[int]) -> int:
        '''
        希望將數組劃分成m個，並且要用完所有元素，然後劃分出來的子數組的AND 要等於當下的index andValues 數值 並且根據現在的
        子數組尾數字當作是該子數組的代表 計算最小的所有代表總和
        我的理解過程：
        1. 首先 AND過程會越來越小，當某個數字比當前數字還大的時候可以往下走 但是一但小於之後就代表不可這樣切分
        2. 這題會希望你在 n * m 時間下完成 所以可以想像狀態會定義成 走到 i的時候 可以切分出 j 組的最小總和是多少
        3. 這裡之後去看AND數學定義了 才知道AND往下走只會有lgU種結果 所以把他加入狀態中就行了
        '''
        n = len(nums)
        m = len(andValues)
        @cache
        def dfs(i:int, j:int, nd:int) -> int:
            if i == n:
                return 0 if j == m else inf
            nd &= nums[i]
            if j == m or nd < andValues[j]:
                return inf
            ret = dfs(i + 1, j, nd) # 不以他為結尾繼續做and
            if nd == andValues[j]:
                tmp = dfs(i + 1, j + 1, -1) + nums[i]
                if tmp < ret: ret = tmp
            return ret
        ans = dfs(0, 0, -1)
        return ans if ans != inf else -1
