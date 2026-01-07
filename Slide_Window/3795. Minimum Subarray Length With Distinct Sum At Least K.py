# TC:O(n) SC:O(n)
class Solution:
    def minLength(self, nums: List[int], k: int) -> int:
        n = len(nums)
        mp = defaultdict(int)
        i = j = tot = 0
        ans = inf
        while j < n:
            while j < n and tot < k:
                mp[nums[j]] += 1
                if mp[nums[j]] == 1:
                    tot += nums[j]
                j += 1
            # 找到超過ｋ的長度
            while i < n and tot >= k:
                ans = min(ans, j - i)
                mp[nums[i]] -= 1
                if mp[nums[i]] == 0:
                    tot -= nums[i]
                i += 1
        return ans if ans != inf else -1
            
                    
