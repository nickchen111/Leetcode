class Solution:
    def maxCapacity(self, costs: list[int], capacity: list[int], budget: int) -> int:
        nums = sorted(zip(costs, capacity))
        n = len(nums)
        
        prev_max = [0] * n
        for k in range(n):
            prev_max[k] = max(nums[k][1], prev_max[k - 1])
            
        ans = 0
        for i in range(n):
            cost_i, cap_i = nums[i]
            if cost_i < budget:
                ans = max(ans, cap_i)
            
            rem_budget = budget - cost_i - 1
            if rem_budget <= 0:
                continue
            
            limit = i - 1
            if limit >= 0:
                found_idx = bisect_right(nums, (rem_budget, inf)) - 1
                j = min(limit, found_idx)
                if j >= 0:
                    ans = max(ans, cap_i + prev_max[j])
                    
        return ans