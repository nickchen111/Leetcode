# TC:O(n) SC:O(n)
class Solution:
    def countSubarrays(self, nums: list[int], k: int, m: int) -> int:
        '''
        至少出現m次，要有剛好k種元素 -> slide window!?
        問說有多少種這種subarray
        這題exact -> 轉成兩個at least相減
        [1, 1, 1, 2, 2] m = k = 2
        '''
        n = len(nums)
        def solve(distinct_limit:int) -> int:
            if distinct_limit == 0:
                return 0
            cnt = defaultdict(int)
            valid_ele = 0
            i = ans = 0
            for j,x in enumerate(nums):
                # 入
                if cnt[x] == m - 1:
                    valid_ele += 1
                cnt[x] += 1
    
                # 出
                while len(cnt) >= distinct_limit and valid_ele >= k:
                    if cnt[nums[i]] == m:
                        valid_ele -= 1
                    cnt[nums[i]] -= 1
                    if cnt[nums[i]] == 0:
                        del cnt[nums[i]]
                    i += 1
                ans += i
            return ans
        return solve(k) - solve(k + 1)
