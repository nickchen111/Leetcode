# 3149. Find the Minimum Cost Array Permutation

# TC:O(n^2 * 2^n) SC:O(15*2^n)
class Solution:
    def findPermutation(self, nums: List[int]) -> List[int]:
        n = len(nums)
        # 排列型且跟相鄰有關DP 遞歸過程帶的是枚舉的狀態以及上一個填什麼

        @cache
        def dfs(i: int, j: int)->int:
            if i == (1<<n)-1:
                return abs(j - nums[0])
            res = inf
            for k in range(n):
                if (i>>k)&1:
                    continue
                res = min(res, dfs(i | (1<<k), k) + abs(j - nums[k]))
            return res

        ans = []
        def print_ans(i: int, j: int) -> None:
            ans.append(j)
            if i == (1<<n)-1:
                return
            res = dfs(i,j)
            for k in range(n):
                if (i>>k)&1:
                    continue
                if (dfs(i | (1<<k), k) + abs(j - nums[k])) == res:
                    print_ans(i | (1<<k), k)
                    break

        print_ans(1,0)
        return ans
