# TC:O(n + q) SC:O(n + q)
class Solution:
    def countStableSubarrays(self, nums: List[int], queries: List[List[int]]) -> List[int]:
        n = len(nums)
        # 滑窗概念
        pre = [0] * (n + 1)
        cnt = 0
        for i, x in enumerate(nums):
            if i > 0 and x < nums[i - 1]:
                cnt = 0
            cnt += 1
            pre[i + 1] = pre[i] + cnt
        nxt = [0] * n
        nxt[-1] = n # 下一個遞增的起點
        for i in range(n - 2, -1, -1):
            nxt[i] = nxt[i + 1] if nums[i] <= nums[i + 1] else i + 1
        ans = []
        for l, r in queries:
            l2 = nxt[l]
            if l2 > r:
                m = r - l + 1
                ans.append(m * (m + 1) // 2)
            else:
                m = l2 - l
                ans.append(m * (m + 1) // 2 + pre[r + 1] - pre[l2])
        return ans
        '''
        離線查詢做法 TC:O(qlogq + n + q) SC:O(n + q)
        end = [0] * n
        end[n-1] = n-1
        for i in range(n-2, -1, -1):
            if nums[i] <= nums[i+1]:
                end[i] = end[i+1]
            else:
                end[i] = i
        qs = [(l, r, qi) for qi, (l, r) in enumerate(queries)]
        qs.sort(key=lambda x: x[1])
        ans = [0] * len(queries)
        p = 0
        pre_cnt = [0]
        pre_sum_end = [0]
        for l,r,qi in qs:
            while p < n and end[p] <= r:
                pre_cnt.append(pre_cnt[-1] + 1)
                pre_sum_end.append(pre_sum_end[-1] + end[p])
                p += 1
            length = r - l + 1
            total = length * (length + 1) // 2
            cnt_active = pre_cnt[min(r + 1, len(pre_cnt) - 1)] - pre_cnt[min(l, len(pre_cnt) - 1)]
            sum_end_active = pre_sum_end[min(r + 1, len(pre_sum_end) - 1)] - pre_sum_end[min(l, len(pre_sum_end) - 1)]
            ans[qi] = total - r * cnt_active + sum_end_active
        return ans
        '''
