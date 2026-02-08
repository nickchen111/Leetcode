# TC:O(n) SC:O(n)
class Solution:
    def countSubarrays(self, nums: List[int], k: int) -> int:
        '''
        找出有多少個subarray cost <= k
        要維護最大與最小
        '''
        mn_q = deque()
        mx_q = deque()
        n = len(nums)
        ans = i = 0
        for j in range(n):
            # 入
            while mn_q and mn_q[-1] > nums[j]:
                mn_q.pop()
            while mx_q and mx_q[-1] < nums[j]:
                mx_q.pop()
            mn_q.append(nums[j])
            mx_q.append(nums[j])
            # 出
            while (mx_q[0] - mn_q[0]) * (j - i + 1) > k:
                if nums[i] == mx_q[0]:
                    mx_q.popleft()
                elif nums[i] == mn_q[0]:
                    mn_q.popleft()
                i += 1
            ans += j - i + 1
        return ans
