# Stack
class Solution:
    def maxCapacity(self, costs: list[int], capacity: list[int], budget: int) -> int:
        nums = [(cost, cap) for cost, cap in zip(costs, capacity) if cost < budget]
        nums.sort(key=lambda x:x[0])
        n = len(nums)
        
        st = [(0, 0)]
        ans = 0
        for i, (cost, cap) in enumerate(nums):
            while st and st[-1][0] + cost >= budget:
                st.pop()
            ans = max(ans, cap + st[-1][1])
            if cap > st[-1][1]:
                st.append((cost, cap))
        return ans


# TC:O(nlogn) SC:O(n)
class Solution:
    def maxCapacity(self, costs: list[int], capacity: list[int], budget: int) -> int:
        nums = [(cost, cap) for cost, cap in zip(costs, capacity) if cost < budget]
        nums.sort(key=lambda x:x[0])
        n = len(nums)
        
        prev_max = [0] * (n + 1)
        ans = 0
        for i, (cost, cap) in enumerate(nums):
            j = bisect_left(range(i), budget - cost, key=lambda j:nums[j][0])
            ans = max(ans, cap + prev_max[j])
            prev_max[i + 1] = max(prev_max[i], cap)
                    
        return ans
