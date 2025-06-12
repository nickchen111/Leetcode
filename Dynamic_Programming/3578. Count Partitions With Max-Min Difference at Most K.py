# TC:O(n) SC:O(n)
class Solution:
    def countPartitions(self, nums: List[int], k: int) -> int:
        MOD = 10 ** 9 + 7
        n = len(nums)
        prefix = [0] * (n + 1)
        prefix[0] = 1
        min_q = deque()
        max_q = deque()

        l = 0
        for r in range(n):
            while min_q and nums[r] < nums[min_q[-1]]:
                min_q.pop()
            min_q.append(r)

            while max_q and nums[r] > nums[max_q[-1]]:
                max_q.pop()
            max_q.append(r)

            while nums[max_q[0]] - nums[min_q[0]] > k:
                l += 1
                if min_q[0] < l:
                    min_q.popleft()
                if max_q[0] < l:
                    max_q.popleft()
            if l == 0:
                cur = prefix[r]
            else:
                cur = (prefix[r] - prefix[l - 1] + MOD) % MOD
            prefix[r+1] = (prefix[r] + cur) % MOD
        return cur
