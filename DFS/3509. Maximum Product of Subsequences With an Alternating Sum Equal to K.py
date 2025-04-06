# TC:O(n * 162 * 354 * 2 ) SC:O(n * 162 * 2 * 2 * 2)
class Solution:
    def maxProduct(self, nums: List[int], k: int, limit: int) -> int:
        n = len(nums)
        one = False
        @cache 
        def dfs(i: int, total: int, pos: bool, empty: bool, zero:bool) -> Set[int]:
            nonlocal one
            if i == n:
                if not empty and total == k and not zero:
                    return {1}
                elif not empty and total == k and zero:
                    return {0}
                else: return set()

            ret = dfs(i + 1, total, pos, empty, zero) # 不選
            x = nums[i]
            nxt = dfs(i + 1, total + (-x if not pos else x), not pos, False, zero or x == 0)
            if x == 0 and nxt:
                ret.add(0)
                return ret
            for y in nxt:
                if y * x <= limit:
                    ret.add(y * x)
                if y * x == 1:
                    one = True
            return ret

        st = dfs(0, 0, True, True, False)
        ans = -1
        # print(st)
        for x in st:
            if (x == 1 and one) or x != 1:
                ans = max(ans, x)
        return ans
