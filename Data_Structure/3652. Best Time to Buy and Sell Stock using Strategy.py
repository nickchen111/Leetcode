# TC:O(n) SC:O(n)
class Solution:
    def maxProfit(self, prices: List[int], strategy: List[int], k: int) -> int:
        '''
        前綴和去解 然後規劃每一段固定長度可以獲得的總值
        '''
        nums = []
        n = len(prices)
        for i in range(n):
            nums.append(prices[i] * strategy[i])
        prefix = [0] * (n + 1)
        for i in range(n):
            prefix[i + 1] = prefix[i] + nums[i]
        i, j = 0, k
        cur = 0
        for left in range(k):
            if left < k // 2:
                continue
            cur += prices[left]
        # print(prefix[-1], prefix[k], cur)
        ans = max(prefix[-1], prefix[-1] - prefix[k] + cur)
        while j < n:
            cur += prices[j]
            if j - i + 1 > k:
                cur -= prices[j - k // 2]
                i += 1
            ans = max(ans, prefix[-1] - (prefix[j + 1] - prefix[i]) + cur)
            j += 1
        return ans
            
            
